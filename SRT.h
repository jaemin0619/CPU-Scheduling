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
            return a->at > b->at; // ���� �ð��� ������ ���� ������ ���μ����� ����
        }
        return a->rt > b->rt; // ���� ���� �ð��� ª�� ������ ����
    }
};

void SRT_Scheduling(vector<Process>& processes) {
    int n = processes.size();

    // ���� �ð� ������ ����
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
        });

    // �켱���� ť�� ����Ͽ� ���� ��� ���� ���μ����� ����
    priority_queue<Process*, vector<Process*>, CompareRemainingTime> ready_queue;

    // ���� �ð� �� �� ��� �ð�, �� ��ȯ �ð�, �� ���� �ð� �ʱ�ȭ
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;
    int completed = 0;
    vector<bool> first_response(n, true);  // ù ������ ����ϱ� ���� ����

    // ��Ʈ ��Ʈ�� ������ ����
    vector<GanttBlock> gantt_chart;

    // ���� ���� �ð��� ������ ����
    vector<int> remaining_time(n);
    for (int i = 0; i < n; ++i) {
        remaining_time[i] = processes[i].rt;
        processes[i].response_time = -1; // ���� �ð� �ʱ�ȭ
    }

    while (completed != n) {
        // ���� �ð��� ������ ���μ����� ���� ��� ť�� �߰�
        for (int i = 0; i < n; ++i) {
            if (processes[i].at == current_time) {
                ready_queue.push(&processes[i]);
            }
        }

        // ���� ��� ť�� ������� ���� ���
        if (!ready_queue.empty()) {
            // ���� �ð��� ���� ª�� ���μ��� ����
            Process* current_process = ready_queue.top();
            ready_queue.pop();

            // ���� ���μ����� ���� �ð��� �������� ���� ���
            int idx = current_process - &processes[0];
            if (first_response[idx]) {
                current_process->response_time = current_time - current_process->at;
                first_response[idx] = false;  // ù ���� ���
            }

            // ��Ʈ ��Ʈ ������Ʈ
            if (!gantt_chart.empty() && gantt_chart.back().pid == current_process->id) {
                gantt_chart.back().end_time++;
            }
            else {
                gantt_chart.push_back({ current_process->id, current_time, current_time + 1 });
            }

            // ���� ���μ����� ���� �ð��� ���ҽ�Ŵ
            remaining_time[idx]--;
            current_time++;

            // ���� ���μ����� ������ �Ϸ�� ���
            if (remaining_time[idx] == 0) {
                // ��ȯ �ð�, ��� �ð�, �ҿ� �ð� ���
                current_process->return_time = current_time;
                current_process->tt = current_process->return_time - current_process->at;
                current_process->wt = current_process->tt - current_process->rt;

                // �� ��ȯ �ð�, �� ��� �ð�, �� ���� �ð� ������Ʈ
                total_waiting_time += current_process->wt;
                total_turnaround_time += current_process->tt;
                total_response_time += current_process->response_time;

                completed++;
            }
            else { // ���� ���μ����� ������ �Ϸ���� ���� ��� �ٽ� ���� ��� ť�� �߰�
                ready_queue.push(current_process);
            }
        }
        else { // ���� ��� ���� ���μ����� ���� ��� �ð� ����
            current_time++;
        }
    }

    // ��Ʈ ��Ʈ �� ��� ���
    cout << "\tShortest Remaining Time (SRT) Scheduling\n";
    print_gantt_chart(gantt_chart);
    view_table(processes);

    // ��� ��� �ð�, ��� ��ȯ �ð�, ��� ���� �ð� ���
    cout << "\nAverage Waiting Time = " << fixed << setprecision(2) << (double)total_waiting_time / n << endl;
    cout << "Average Turnaround Time = " << fixed << setprecision(2) << (double)total_turnaround_time / n << endl;
    cout << "Average Response Time = " << fixed << setprecision(2) << (double)total_response_time / n << endl;
}

#endif // SRT_H
