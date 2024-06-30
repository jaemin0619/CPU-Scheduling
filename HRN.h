#ifndef HRN_H
#define HRN_H

#include "Process.h"
#include "Gantt_chart.h"
#include "View_Table.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void HRN_Scheduling(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    int completed = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    vector<bool> is_completed(n, false);
    vector<GanttBlock> gantt_chart;

    while (completed != n) {
        // 가장 높은 응답 비율을 가진 프로세스 선택
        int idx = -1;
        double max_response_ratio = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].at <= current_time && !is_completed[i]) {
                int waiting_time = current_time - processes[i].at;
                double response_ratio = (double)(waiting_time + processes[i].rt) / processes[i].rt;

                if (response_ratio > max_response_ratio) {
                    max_response_ratio = response_ratio;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            Process& current_process = processes[idx];

            // 응답 시간 설정
            if (current_process.response_time == -1) {
                current_process.response_time = current_time - current_process.at;
            }

            // 간트 차트 업데이트
            gantt_chart.push_back({ current_process.id, current_time, current_time + current_process.rt });

            // 프로세스 실행
            current_time += current_process.rt;
            current_process.return_time = current_time;
            current_process.tt = current_process.return_time - current_process.at;
            current_process.wt = current_process.tt - current_process.rt;

            // 총 대기 시간, 총 반환 시간, 총 응답 시간 업데이트
            total_waiting_time += current_process.wt;
            total_turnaround_time += current_process.tt;
            total_response_time += current_process.response_time;

            // 프로세스 완료 상태 업데이트
            is_completed[idx] = true;
            completed++;
        }
        else {
            current_time++;
        }
    }

    // 간트 차트 및 결과 출력
    cout << "\tHighest Response Ratio Next (HRN) Scheduling\n";
    print_gantt_chart(gantt_chart);
    view_table(processes);

    // 평균 대기 시간, 평균 반환 시간, 평균 응답 시간 출력
    cout << "\nAverage Waiting Time = " << fixed << setprecision(2) << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time = " << fixed << setprecision(2) << (double)total_turnaround_time / n << endl;
    cout << "Average Response Time = " << fixed << setprecision(2) << (double)total_response_time / n << endl;
}

#endif // HRN_H