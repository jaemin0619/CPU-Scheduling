#ifndef FCFS_H
#define FCFS_H
#include "Process.h"
#include "Gantt_chart.h"
#include "View_Table.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

// FCFS 스케줄링 함수
void FCFS_Scheduling(vector<Process>& p) {
    cout << "\tFCFS" << endl;
    int total_waiting_time = 0;
    int total_turnAround_time = 0;
    int total_response_time = 0;

    vector<GanttBlock> gantt_chart;

    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
    });

    int current_time = 0;

    for (size_t i = 0; i < p.size(); i++) {
        if (current_time < p[i].at) {
            current_time = p[i].at;
        }

        p[i].wt = current_time - p[i].at; // 대기 시간 = 현재 시간 - 도착 시간
        p[i].response_time = p[i].wt; // 응답 시간 = 대기 시간
        p[i].return_time = current_time + p[i].rt; // 반환 시간 = 현재 시간 + 실행 시간
        p[i].tt = p[i].return_time - p[i].at; // 소요 시간 = 반환 시간 - 도착 시간

        gantt_chart.push_back({ p[i].id, current_time, p[i].return_time });

        current_time += p[i].rt; // 현재 시간 업데이트

        total_waiting_time += p[i].wt;
        total_turnAround_time += p[i].tt;
        total_response_time += p[i].response_time;
    }

    print_gantt_chart(gantt_chart);
    view_table(p);

    cout << endl;
    cout << "Average Total Waiting time = " << fixed << setprecision(2) << (double)total_waiting_time / (double)p.size() << endl;
    cout << "Average Total turnAround time = " << fixed << setprecision(2) << (double)total_turnAround_time / (double)p.size() << endl;
    cout << "Average Total Response time = " << fixed << setprecision(2) << (double)total_response_time / (double)p.size() << endl;
}

#endif // FCFS_H
