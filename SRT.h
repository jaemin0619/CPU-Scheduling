#ifndef SRT_H
#define SRT_H

#include "Process.h"
#include "Gantt_chart.h"
#include "View_Table.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct CompareRemainingTime {
    bool operator()(const Process* a, const Process* b) {
        if (a->rt == b->rt) {
            return a->at > b->at; // 실행 시간이 같으면 먼저 도착한 프로세스를 선택
        }
        return a->rt > b->rt; // 남은 실행 시간이 짧은 순으로 정렬
    }
};

void SRT_Scheduling(vector<Process>& processes) {
    int n = processes.size();

    // 도착 시간 순으로 정렬
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
        });

    // 우선순위 큐를 사용하여 실행 대기 중인 프로세스를 관리
    priority_queue<Process*, vector<Process*>, CompareRemainingTime> ready_queue;

    // 현재 시간 및 총 대기 시간, 총 반환 시간, 총 응답 시간 초기화
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;
    int completed = 0;
    vector<bool> first_response(n, true);  // 첫 실행을 기록하기 위한 벡터

    // 간트 차트를 저장할 벡터
    vector<GanttBlock> gantt_chart;

    // 남은 실행 시간을 추적할 벡터
    vector<int> remaining_time(n);
    for (int i = 0; i < n; ++i) {
        remaining_time[i] = processes[i].rt;
        processes[i].response_time = -1; // 응답 시간 초기화
    }

    while (completed != n) {
        // 현재 시간에 도착한 프로세스를 실행 대기 큐에 추가
        for (int i = 0; i < n; ++i) {
            if (processes[i].at == current_time) {
                ready_queue.push(&processes[i]);
            }
        }

        // 실행 대기 큐가 비어있지 않은 경우
        if (!ready_queue.empty()) {
            // 실행 시간이 가장 짧은 프로세스 선택
            Process* current_process = ready_queue.top();
            ready_queue.pop();

            // 현재 프로세스의 응답 시간이 설정되지 않은 경우
            int idx = current_process - &processes[0];
            if (first_response[idx]) {
                current_process->response_time = current_time - current_process->at;
                first_response[idx] = false;  // 첫 실행 기록
            }

            // 간트 차트 업데이트
            if (!gantt_chart.empty() && gantt_chart.back().pid == current_process->id) {
                gantt_chart.back().end_time++;
            }
            else {
                gantt_chart.push_back({ current_process->id, current_time, current_time + 1 });
            }

            // 현재 프로세스의 실행 시간을 감소시킴
            remaining_time[idx]--;
            current_time++;

            // 현재 프로세스의 실행이 완료된 경우
            if (remaining_time[idx] == 0) {
                // 반환 시간, 대기 시간, 소요 시간 계산
                current_process->return_time = current_time;
                current_process->tt = current_process->return_time - current_process->at;
                current_process->wt = current_process->tt - current_process->rt;

                // 총 반환 시간, 총 대기 시간, 총 응답 시간 업데이트
                total_waiting_time += current_process->wt;
                total_turnaround_time += current_process->tt;
                total_response_time += current_process->response_time;

                completed++;
            }
            else { // 현재 프로세스의 실행이 완료되지 않은 경우 다시 실행 대기 큐에 추가
                ready_queue.push(current_process);
            }
        }
        else { // 실행 대기 중인 프로세스가 없는 경우 시간 증가
            current_time++;
        }
    }

    // 간트 차트 및 결과 출력
    cout << "\tShortest Remaining Time (SRT) Scheduling\n";
    print_gantt_chart(gantt_chart);
    view_table(processes);

    // 평균 대기 시간, 평균 반환 시간, 평균 응답 시간 출력
    cout << "\nAverage Waiting Time = " << fixed << setprecision(2) << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time = " << fixed << setprecision(2) << (double)total_turnaround_time / n << endl;
    cout << "Average Response Time = " << fixed << setprecision(2) << (double)total_response_time / n << endl;
}

#endif // SRT_H
