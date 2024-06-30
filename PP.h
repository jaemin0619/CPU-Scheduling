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
            return a->at > b->at; // ���� �ð��� ������ ���� ������ ���μ����� ����
        }
        return a->priority > b->priority; // �켱������ �������� ���� ����
    }
};

void PP_Scheduling(vector<Process>& p) {
    cout << "\tPreemptive Priority Scheduling" << endl;

    int n = p.size();
    int current_time = 0;
    int completed = 0;
    vector<GanttBlock> gantt_chart;
    priority_queue<Process*, vector<Process*>, ComparePriority> ready_queue;

    // �ʱ�ȭ �� ���� �ð� ����
    for (auto& proc : p) {
        proc.completed = false;
        proc.response_time = -1; // ���� ������ ������ ǥ��
    }

    vector<int> remaining_time(n); // �� ���μ����� ���� ���� �ð��� ������ ����
    for (int i = 0; i < n; i++) {
        remaining_time[i] = p[i].rt; // �ʱ� ���� ���� �ð��� ���� ���� �ð����� ����
    }

    while (completed != n) {
        // ���� �ð��� ������ ���μ����� �غ� ť�� �߰�
        for (auto& proc : p) {
            if (proc.at == current_time && remaining_time[&proc - &p[0]] > 0) {
                ready_queue.push(&proc);
            }
        }

        if (!ready_queue.empty()) {
            Process* current_process = ready_queue.top();
            ready_queue.pop();

            // ��Ʈ ��Ʈ�� ���μ��� ���� ���� �߰�
            if (!gantt_chart.empty() && gantt_chart.back().pid == current_process->id) {
                gantt_chart.back().end_time++;
            }
            else {
                gantt_chart.push_back({ current_process->id, current_time, current_time + 1 });
            }

            // ���μ��� ����
            int idx = current_process - &p[0];

            // ���� �ð� ����: ó�� ����� ���� ����
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
                ready_queue.push(current_process); // ���� �Ϸ���� ���� ��� �ٽ� ť�� �߰�
            }
        }
        else {
            current_time++;
        }
    }

    // �� ��� �ð�, �ҿ� �ð�, ���� �ð� ���
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    for (auto& proc : p) {
        total_waiting_time += proc.wt;
        total_turnaround_time += proc.tt;
        total_response_time += proc.response_time;
    }

    // ��Ʈ ��Ʈ �� ���̺� ���
    print_gantt_chart(gantt_chart);
    view_table(p);

    cout << endl;
    cout << "Average Total Waiting time = " << fixed << setprecision(2) << (double)total_waiting_time / n << endl;
    cout << "Average Total turnAround time = " << fixed << setprecision(2) << (double)total_turnaround_time / n << endl;
    cout << "Average Total Response time = " << fixed << setprecision(2) << (double)total_response_time / n << endl;
}

#endif // PREEMPTIVE_PRIORITY_H
