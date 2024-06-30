#ifndef VIEW_TABLE_H
#define VIEW_TABLE_H
#include "Process.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm> 
using namespace std;

void view_table(const vector<Process>& p) {
    // �� ���� �ִ� ���̸� ������ �迭�� �ʱ�ȭ
    vector<size_t> max_lengths = { 4, 9, 13, 9, 12, 15, 13, 16 }; // �� ���� �ʱ� �ʺ� ����

    // �� ���� �ִ� ���̸� ���
    for (const auto& process : p) {
        max_lengths[0] = max(max_lengths[0], process.id.length());
        max_lengths[1] = max(max_lengths[1], to_string(process.rt).length());
        max_lengths[2] = max(max_lengths[2], to_string(process.at).length());
        max_lengths[3] = max(max_lengths[3], to_string(process.priority).length());
        max_lengths[4] = max(max_lengths[4], to_string(process.return_time).length());
        max_lengths[5] = max(max_lengths[5], to_string(process.response_time).length());
        max_lengths[6] = max(max_lengths[6], to_string(process.wt).length());
        max_lengths[7] = max(max_lengths[7], to_string(process.tt).length());
    }

    // ���̺� ��� ���
    cout << "+";
    for (size_t i = 0; i < max_lengths.size(); ++i) {
        cout << string(max_lengths[i] + 2, '-'); // ���̺� ����� �� �� ���
        if (i < max_lengths.size() - 1) {
            cout << "+"; // �� ������ ���
        }
    }
    cout << "+\n";

    cout << "| " << setw(max_lengths[0]) << left << "PID" << " | "
        << setw(max_lengths[1]) << left << "Run Time" << " | "
        << setw(max_lengths[2]) << left << "Arrival Time" << " | "
        << setw(max_lengths[3]) << left << "Priority" << " | "
        << setw(max_lengths[4]) << left << "Return Time" << " | "
        << setw(max_lengths[5]) << left << "Response Time" << " | "
        << setw(max_lengths[6]) << left << "Waiting Time" << " | "
        << setw(max_lengths[7]) << left << "TurnAround Time" << " |\n";

    // ���̺� ���� ���
    cout << "+";
    for (size_t i = 0; i < max_lengths.size(); ++i) {
        cout << string(max_lengths[i] + 2, '-');
        if (i < max_lengths.size() - 1) {
            cout << "+"; // �� ������ ���
        }
    }
    cout << "+\n";

    // �� ���μ��� ���� ���
    for (const auto& process : p) {
        cout << "| " << setw(max_lengths[0]) << left << process.id << " | "
            << setw(max_lengths[1]) << left << process.rt << " | "
            << setw(max_lengths[2]) << left << process.at << " | "
            << setw(max_lengths[3]) << left << process.priority << " | "
            << setw(max_lengths[4]) << left << process.return_time << " | "
            << setw(max_lengths[5]) << left << process.response_time << " | "
            << setw(max_lengths[6]) << left << process.wt << " | "
            << setw(max_lengths[7]) << left << process.tt << " |\n";
    }

    // ���̺� ������ �κ� ���
    cout << "+";
    for (size_t i = 0; i < max_lengths.size(); ++i) {
        cout << string(max_lengths[i] + 2, '-');
        if (i < max_lengths.size() - 1) {
            cout << "+"; // �� ������ ���
        }
    }
    cout << "+\n";
}

#endif // VIEW_TABLE_H
