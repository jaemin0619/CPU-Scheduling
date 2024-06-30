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

// ���� �κ� �����ٸ� �Լ�
void RR_Scheduling(vector<Process>& processes, Quantum quantum) {
    cout << "\tRound Robin (RR)" << endl;

    int total_waiting_time = 0;
    int total_turnAround_time = 0;
    int total_response_time = 0;
    int num_processes = processes.size();

    vector<Process> p = processes; // ���� ���μ����� �����Ͽ� ���
    vector<GanttBlock> gantt_chart;

    queue<Process*> ready_queue;
    int current_time = 0;

    // ���� �ð� ������ ����
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
        });

    size_t index = 0;
    while (index < p.size() || !ready_queue.empty()) {
        // ������ ���μ����� �غ� ť�� �߰�
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

        // ù �����̸� ���� �ð� ���
        if (current_process->response_time == -1) {
            current_process->response_time = current_time - current_process->at;
            total_response_time += current_process->response_time; // ���� �ð� ����
        }

        int execution_time = min(quantum, current_process->rt);
        gantt_chart.push_back({ current_process->id, current_time, current_time + execution_time });
        current_time += execution_time;
        current_process->rt -= execution_time;

        // ������ ������ �ʾ����� �ٽ� ť�� �߰�
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

        // ���� ���μ������� �����ϴ� ���� ��ٸ�
        while (index < p.size() && p[index].at <= current_time) {
            ready_queue.push(&p[index]);
            index++;
        }
    }

    // p ������ �����͸� ���� processes ���Ϳ� �����Ͽ� ���� �ð��� �ùٸ��� �����ǵ��� ��
    for (size_t i = 0; i < processes.size(); i++) {
        processes[i].wt = p[i].wt;
        processes[i].tt = p[i].tt;
        processes[i].response_time = p[i].response_time;
        processes[i].return_time = p[i].return_time;
    }

    // ��Ʈ ��Ʈ�� ���̺� ���
    print_gantt_chart(gantt_chart);
    view_table(processes); // ���� ���μ��� ���͸� ����Ͽ� ���� ���� �ð��� ǥ��

    // ��� ��� �ð�, ��ȯ �ð�, �ҿ� �ð� ���
    cout << endl;
    cout << "Average Total Waiting time = " << fixed << setprecision(2) << (double)total_waiting_time / (double)num_processes << endl;
    cout << "Average Total turnAround time = " << fixed << setprecision(2) << (double)total_turnAround_time / (double)num_processes << endl;
    cout << "Average Total Response time = " << fixed << setprecision(2) << (double)total_response_time / (double)num_processes << endl;
}

#endif // RR_H
