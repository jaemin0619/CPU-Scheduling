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
    int current_time = 0; // ���� �ð��� ������ ����
    vector<Process> result; // ����� ������� ���μ����� ������ ����
    vector<Process> ready_queue; // �غ� ť

    while (!p.empty() || !ready_queue.empty()) { // ��� ���μ����� ó���� ������ �ݺ�
        // ���� �ð��� ���� �ð����� �۰ų� ���� ���μ����� �غ� ť�� �߰�
        auto it = p.begin();
        while (it != p.end() && it->at <= current_time) {
            ready_queue.push_back(*it);
            it = p.erase(it);
        }
        if (!ready_queue.empty()) {
            // �غ� ť���� �켱������ ���� ���� ���μ��� ����
            auto next_process = min_element(ready_queue.begin(), ready_queue.end(), [](const Process& a, const Process& b) {
                if (a.priority == b.priority) {
                    return a.at < b.at;
                }
                return a.priority < b.priority;
                });

            // ���� ���μ����� ������ ����
            if (current_time < next_process->at) {
                current_time = next_process->at; // ���� �ð� ����
            }
            next_process->wt = current_time - next_process->at; // ��� �ð� ���
            next_process->response_time = next_process->wt; // ���� �ð� ����
            current_time += next_process->rt; // ���� �ð� ����
            next_process->return_time = current_time; // ��ȯ �ð� ����
            next_process->tt = next_process->return_time - next_process->at; // �ҿ� �ð� ����

            result.push_back(*next_process); // ����� ���μ����� ��� ���Ϳ� �߰�
            ready_queue.erase(next_process); // �غ� ť���� ���μ����� ����
        }
        else {
            current_time++; // �غ� ť�� ����ִٸ� �ð� ����
        }
    }

    // ��� ���͸� ���� ���Ϳ� ����
    p = result;
}

// NPP �����ٸ� �Լ�
void NPP_Scheduling(vector<Process>& p) {
    cout << "\tNPP" << endl;
    int total_waiting_time = 0;
    int total_turnAround_time = 0;
    int total_response_time = 0;

    vector<GanttBlock> gantt_chart;

    // NPP �����ٸ� �˰��� ����
    NPP_Process_Time(p);

    for (const auto& process : p) {
        // ��Ʈ ��Ʈ�� �߰�
        gantt_chart.push_back({ process.id, process.return_time - process.rt, process.return_time });

        // �� ��� �ð�, ��ȯ �ð�, �ҿ� �ð��� ����
        total_waiting_time += process.wt;
        total_turnAround_time += process.tt;
        total_response_time += process.response_time;
    }

    // ��Ʈ ��Ʈ�� ���̺� ���
    print_gantt_chart(gantt_chart);
    view_table(p);

    // ��� ��� �ð�, ��ȯ �ð�, �ҿ� �ð� ���
    cout << endl;
    cout << "Average Total Waiting time = " << fixed << setprecision(2) << (double)total_waiting_time / (double)p.size() << endl;
    cout << "Average Total turnAround time = " << fixed << setprecision(2) << (double)total_turnAround_time / (double)p.size() << endl;
    cout << "Average Total Response time = " << fixed << setprecision(2) << (double)total_response_time / (double)p.size() << endl;
}

#endif // NPP_H
