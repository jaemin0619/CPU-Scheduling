#ifndef Function_to_Sorting_H
#define Function_to_Sorting_H
#include <algorithm>
#include<vector>
#include "Process.h"
using namespace std;

//반환시간 기준으로  함수 - 오름차순
bool compare_return_time(const Process& a, const Process& b)
{
    return a.return_time < b.return_time;
}

//반환시간 기준으로 정렬하는 함수
void sort_return_time(vector<Process>& processes)
{
    sort(processes.begin(), processes.end(), compare_return_time);
}
// 우선순위 기준으로 비교 함수 - 오름차순
bool compare_priority_time(const Process& a, const Process& b) {
    if (a.priority != b.priority) {
        return a.priority < b.priority;
    }
    else {
        return a.at < b.at;
    }
}

// 우선순위 기준으로 정렬하는 함수
void sort_priority_time(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compare_priority_time);
}

// 실행시간 기준으로 비교 함수 - 오름차순
bool compare_run_time(const Process& a, const Process& b) {
    return a.rt < b.rt;
}

// 실행시간 기준으로 정렬하는 함수
void sort_run_time(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compare_run_time);
}

// 도착시간 기준으로 비교 함수 - 오름차순
bool compare_arrival_time(const Process& a, const Process& b) {
    return a.at < b.at;
}

// 도착시간 기준으로 정렬하는 함수
void sort_arrival_time(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compare_arrival_time);
}
#endif Function_to_Sorting_H