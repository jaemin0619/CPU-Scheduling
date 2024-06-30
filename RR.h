#ifndef RR_H
#define RR_H

#include "Process.h"
#include "Gantt_chart.h"
#include "View_Table.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

using namespace std;

// 라운드 로빈 스케줄링 함수
void RR_Scheduling(vector<Process>& processes, Quantum quantum) {
    cout << "\tRound Robin (RR)" << endl;

    int total_waiting_time = 0;
    int total_turnAround_time = 0;
    int total_response_time = 0;
    int num_processes = processes.size();

    vector<Process> p = processes; // 원래 프로세스를 복사하여 사용
    vector<GanttBlock> gantt_chart;

    queue<Process*> ready_queue;
    int current_time = 0;

    // 도착 시간 순으로 정렬
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
        });

    size_t index = 0;
    while (index < p.size() || !ready_queue.empty()) {
        // 도착한 프로세스를 준비 큐에 추가
        while (index < p.size() && p[index].at <= current_time) {
            ready_queue.push(&p[index]);
            index++;
        }

        if (ready_queue.empty() && index < p.size()) {
            current_time = p[index].at;
            continue;
        }

        Process* current_process = ready_queue.front();
        ready_queue.pop();

        // 첫 실행이면 응답 시간 기록
        if (current_process->response_time == -1) {
            current_process->response_time = current_time - current_process->at;
            total_response_time += current_process->response_time; // 응답 시간 누적
        }

        int execution_time = min(quantum, current_process->rt);
        gantt_chart.push_back({ current_process->id, current_time, current_time + execution_time });
        current_time += execution_time;
        current_process->rt -= execution_time;

        // 실행이 끝나지 않았으면 다시 큐에 추가
        if (current_process->rt > 0) {
            ready_queue.push(current_process);
        }
        else {
            current_process->return_time = current_time;
            current_process->tt = current_process->return_time - current_process->at;
            current_process->wt = current_process->tt - processes[current_process - &p[0]].rt;
            total_waiting_time += current_process->wt;
            total_turnAround_time += current_process->tt;
        }

        // 남은 프로세스들이 도착하는 동안 기다림
        while (index < p.size() && p[index].at <= current_time) {
            ready_queue.push(&p[index]);
            index++;
        }
    }

    // p 벡터의 데이터를 원래 processes 벡터에 복사하여 실행 시간이 올바르게 유지되도록 함
    for (size_t i = 0; i < processes.size(); i++) {
        processes[i].wt = p[i].wt;
        processes[i].tt = p[i].tt;
        processes[i].response_time = p[i].response_time;
        processes[i].return_time = p[i].return_time;
    }

    // 간트 차트와 테이블 출력
    print_gantt_chart(gantt_chart);
    view_table(processes); // 원래 프로세스 벡터를 사용하여 원래 실행 시간을 표시

    // 평균 대기 시간, 반환 시간, 소요 시간 출력
    cout << endl;
    cout << "Average Total Waiting time = " << fixed << setprecision(2) << (double)total_waiting_time / (double)num_processes << endl;
    cout << "Average Total turnAround time = " << fixed << setprecision(2) << (double)total_turnAround_time / (double)num_processes << endl;
    cout << "Average Total Response time = " << fixed << setprecision(2) << (double)total_response_time / (double)num_processes << endl;
}

#endif // RR_H
