#ifndef NPP_H
#define NPP_H

#include "Process.h"
#include "Gantt_chart.h"
#include "View_Table.h"
#include "Function_To_Sorting.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void NPP_Process_Time(vector<Process>& p) {
    int current_time = 0; // 현재 시간을 저장할 변수
    vector<Process> result; // 실행된 순서대로 프로세스를 저장할 벡터
    vector<Process> ready_queue; // 준비 큐

    while (!p.empty() || !ready_queue.empty()) { // 모든 프로세스가 처리될 때까지 반복
        // 도착 시간이 현재 시간보다 작거나 같은 프로세스를 준비 큐에 추가
        auto it = p.begin();
        while (it != p.end() && it->at <= current_time) {
            ready_queue.push_back(*it);
            it = p.erase(it);
        }
        if (!ready_queue.empty()) {
            // 준비 큐에서 우선순위가 가장 높은 프로세스 선택
            auto next_process = min_element(ready_queue.begin(), ready_queue.end(), [](const Process& a, const Process& b) {
                if (a.priority == b.priority) {
                    return a.at < b.at;
                }
                return a.priority < b.priority;
                });

            // 다음 프로세스의 실행을 시작
            if (current_time < next_process->at) {
                current_time = next_process->at; // 현재 시간 갱신
            }
            next_process->wt = current_time - next_process->at; // 대기 시간 계산
            next_process->response_time = next_process->wt; // 응답 시간 갱신
            current_time += next_process->rt; // 현재 시간 갱신
            next_process->return_time = current_time; // 반환 시간 갱신
            next_process->tt = next_process->return_time - next_process->at; // 소요 시간 갱신

            result.push_back(*next_process); // 실행된 프로세스를 결과 벡터에 추가
            ready_queue.erase(next_process); // 준비 큐에서 프로세스를 삭제
        }
        else {
            current_time++; // 준비 큐가 비어있다면 시간 증가
        }
    }

    // 결과 벡터를 원래 벡터에 복사
    p = result;
}

// NPP 스케줄링 함수
void NPP_Scheduling(vector<Process>& p) {
    cout << "\tNPP" << endl;
    int total_waiting_time = 0;
    int total_turnAround_time = 0;
    int total_response_time = 0;

    vector<GanttBlock> gantt_chart;

    // NPP 스케줄링 알고리즘 적용
    NPP_Process_Time(p);

    for (const auto& process : p) {
        // 간트 차트에 추가
        gantt_chart.push_back({ process.id, process.return_time - process.rt, process.return_time });

        // 총 대기 시간, 반환 시간, 소요 시간을 누적
        total_waiting_time += process.wt;
        total_turnAround_time += process.tt;
        total_response_time += process.response_time;
    }

    // 간트 차트와 테이블 출력
    print_gantt_chart(gantt_chart);
    view_table(p);

    // 평균 대기 시간, 반환 시간, 소요 시간 출력
    cout << endl;
    cout << "Average Total Waiting time = " << fixed << setprecision(2) << (double)total_waiting_time / (double)p.size() << endl;
    cout << "Average Total turnAround time = " << fixed << setprecision(2) << (double)total_turnAround_time / (double)p.size() << endl;
    cout << "Average Total Response time = " << fixed << setprecision(2) << (double)total_response_time / (double)p.size() << endl;
}

#endif // NPP_H
