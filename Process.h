#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
// Process ����ü ����
struct Process {
    std::string id;        // ���μ��� ID
    int wt;                // ��� �ð�
    int at;                // ���� �ð�
    int rt;                // ���� �ð�
    int priority;          // �켱����
    int response_time;     // ���� �ð�
    int return_time;       // ��ȯ �ð�
    int tt;                // �ҿ� �ð�
    bool completed;        // �Ϸ� ����

    // Process ����ü�� �⺻ ������
    Process() : wt(0), at(0), rt(0), priority(0), response_time(-1), return_time(0), tt(0), completed(false) {}
};

// Quantum Ÿ�� ����
typedef int Quantum; // �ð� �Ҵ緮

// ���μ��� ���͸� ���� �ð�(at) �������� �����ϴ� �Լ�
void Process_init(std::vector<Process>& p) {
    std::sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
        });
}

#endif // PROCESS_H
