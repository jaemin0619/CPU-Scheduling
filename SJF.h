#ifndef SJF_H
#define SJF_H

#include "Process.h"
#include "Gantt_chart.h"
#include "View_Table.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// ���μ��� �� �ð� ��� �Լ�
void SJF_Process_Time(vector<Process>& p) {
    int current_time = 0; // ������� ���� �ð��� ������ ����
    vector<Process> result; // ����� ������� ���μ����� ������ ����

    while (result.size() < p.size()) {
        // ���� �ð��� ���� �ð����� �۰ų� ���� ���μ��� �� ���� �ð��� ���� ª�� ���μ��� ����
        auto it = min_element(p.begin(), p.end(), [current_time](const Process& a, const Process& b) {
            if (a.completed) return false;
            if (b.completed) return true;
            if (a.at > current_time && b.at > current_time) return a.at < b.at;
            if (a.at > current_time) return false;
            if (b.at > current_time) return true;
            return a.rt < b.rt;
            });

        if (it->at > current_time) {
            current_time = it->at; // ���� �ð� ����
        }

        it->wt = current_time - it->at; // ��� �ð� ���
        current_time += it->rt; // ���� �ð� ����
        it->return_time = current_time; // ��ȯ �ð� ����
        it->tt = it->return_time - it->at; // �ҿ� �ð� ����
        it->response_time = it->wt; // ���� �ð� ����
        it->completed = true; // �Ϸ� ���� ����
        result.push_back(*it); // ����� ���μ����� ��� ���Ϳ� �߰�
    }

    // ��� ���͸� ���� ���Ϳ� ����
    p = result;
}

// SJF �����ٸ� �Լ�
void SJF_Scheduling(vector<Process>& p) {
    cout << "\tSJF" << endl;
    int total_waiting_time = 0;
    int total_turnAround_time = 0;
    int total_response_time = 0;

    vector<GanttBlock> gantt_chart;

    // SJF �����ٸ� �˰��� ����
    SJF_Process_Time(p);

    int current_time = 0;

    for (size_t i = 0; i < p.size(); i++) {
        // ���� �ð��� ���� �ð����� ������ ���� �ð����� �̵�
        if (current_time < p[i].at) {
            current_time = p[i].at;
        }

        // ���μ����� ��ȯ �ð� ���
        p[i].return_time = current_time + p[i].rt;

        // ��Ʈ ��Ʈ�� �߰�
        gantt_chart.push_back({ p[i].id, current_time, p[i].return_time });

        // ���μ����� ���� �ð�, ��� �ð�, �ҿ� �ð� ���
        p[i].response_time = current_time - p[i].at;
        p[i].wt = p[i].response_time;
        p[i].tt = p[i].return_time - p[i].at;

        // �� ��� �ð�, ��ȯ �ð�, �ҿ� �ð��� ����
        total_waiting_time += p[i].wt;
        total_turnAround_time += p[i].tt;
        total_response_time += p[i].response_time;

        // ���� �ð��� ���μ����� ����� �ð����� ������Ʈ
        current_time = p[i].return_time;
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


#endif // SJF_H
