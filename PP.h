#ifndef PREEMPTIVE_PRIORITY_H
#define PREEMPTIVE_PRIORITY_H

#include "Process.h"
#include "Gantt_chart.h"
#include "View_Table.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

using namespace std;

struct ComparePriority {
    bool operator()(const Process* a, const Process* b) {
        if (a->priority == b->priority) {
            return a->at > b->at; // 도착 시간이 같으면 먼저 도착한 프로세스를 선택
        }
        return a->priority > b->priority; // 우선순위가 낮을수록 먼저 실행
    }
};

void PP_Scheduling(vector<Process>& p) {
    cout << "\tPreemptive Priority Scheduling" << endl;

    int n = p.size();
    int current_time = 0;
    int completed = 0;
    vector<GanttBlock> gantt_chart;
    priority_queue<Process*, vector<Process*>, ComparePriority> ready_queue;

    // 초기화 및 응답 시간 설정
    for (auto& proc : p) {
        proc.completed = false;
        proc.response_time = -1; // 아직 응답이 없음을 표시
    }

    vector<int> remaining_time(n); // 각 프로세스의 남은 실행 시간을 저장할 벡터
    for (int i = 0; i < n; i++) {
        remaining_time[i] = p[i].rt; // 초기 남은 실행 시간을 원래 실행 시간으로 설정
    }

    while (completed != n) {
        // 현재 시간에 도착한 프로세스를 준비 큐에 추가
        for (auto& proc : p) {
            if (proc.at == current_time && remaining_time[&proc - &p[0]] > 0) {
                ready_queue.push(&proc);
            }
        }

        if (!ready_queue.empty()) {
            Process* current_process = ready_queue.top();
            ready_queue.pop();

            // 간트 차트에 프로세스 실행 정보 추가
            if (!gantt_chart.empty() && gantt_chart.back().pid == current_process->id) {
                gantt_chart.back().end_time++;
            }
            else {
                gantt_chart.push_back({ current_process->id, current_time, current_time + 1 });
            }

            // 프로세스 실행
            int idx = current_process - &p[0];

            // 응답 시간 설정: 처음 실행될 때만 설정
            if (current_process->response_time == -1) {
                current_process->response_time = current_time - current_process->at;
            }

            remaining_time[idx]--;
            current_time++;

            if (remaining_time[idx] == 0) {
                current_process->return_time = current_time;
                current_process->tt = current_process->return_time - current_process->at;
                current_process->wt = current_process->tt - current_process->rt;
                completed++;
            }
            else {
                ready_queue.push(current_process); // 아직 완료되지 않은 경우 다시 큐에 추가
            }
        }
        else {
            current_time++;
        }
    }

    // 총 대기 시간, 소요 시간, 응답 시간 계산
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    for (auto& proc : p) {
        total_waiting_time += proc.wt;
        total_turnaround_time += proc.tt;
        total_response_time += proc.response_time;
    }

    // 간트 차트 및 테이블 출력
    print_gantt_chart(gantt_chart);
    view_table(p);

    cout << endl;
    cout << "Average Total Waiting time = " << fixed << setprecision(2) << (double)total_waiting_time / n << endl;
    cout << "Average Total turnAround time = " << fixed << setprecision(2) << (double)total_turnaround_time / n << endl;
    cout << "Average Total Response time = " << fixed << setprecision(2) << (double)total_response_time / n << endl;
}

#endif // PREEMPTIVE_PRIORITY_H
