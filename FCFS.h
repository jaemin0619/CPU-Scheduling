#ifndef FCFS_H
#define FCFS_H
#include "Process.h"
#include "Gantt_chart.h"
#include "View_Table.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

// FCFS �����ٸ� �Լ�
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

        p[i].wt = current_time - p[i].at; // ��� �ð� = ���� �ð� - ���� �ð�
        p[i].response_time = p[i].wt; // ���� �ð� = ��� �ð�
        p[i].return_time = current_time + p[i].rt; // ��ȯ �ð� = ���� �ð� + ���� �ð�
        p[i].tt = p[i].return_time - p[i].at; // �ҿ� �ð� = ��ȯ �ð� - ���� �ð�

        gantt_chart.push_back({ p[i].id, current_time, p[i].return_time });

        current_time += p[i].rt; // ���� �ð� ������Ʈ

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
