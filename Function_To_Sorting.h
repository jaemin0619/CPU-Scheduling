#ifndef Function_to_Sorting_H
#define Function_to_Sorting_H
#include <algorithm>
#include<vector>
#include "Process.h"
using namespace std;

//��ȯ�ð� ��������  �Լ� - ��������
bool compare_return_time(const Process& a, const Process& b)
{
    return a.return_time < b.return_time;
}

//��ȯ�ð� �������� �����ϴ� �Լ�
void sort_return_time(vector<Process>& processes)
{
    sort(processes.begin(), processes.end(), compare_return_time);
}
// �켱���� �������� �� �Լ� - ��������
bool compare_priority_time(const Process& a, const Process& b) {
    if (a.priority != b.priority) {
        return a.priority < b.priority;
    }
    else {
        return a.at < b.at;
    }
}

// �켱���� �������� �����ϴ� �Լ�
void sort_priority_time(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compare_priority_time);
}

// ����ð� �������� �� �Լ� - ��������
bool compare_run_time(const Process& a, const Process& b) {
    return a.rt < b.rt;
}

// ����ð� �������� �����ϴ� �Լ�
void sort_run_time(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compare_run_time);
}

// �����ð� �������� �� �Լ� - ��������
bool compare_arrival_time(const Process& a, const Process& b) {
    return a.at < b.at;
}

// �����ð� �������� �����ϴ� �Լ�
void sort_arrival_time(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compare_arrival_time);
}
#endif Function_to_Sorting_H