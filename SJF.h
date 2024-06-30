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

// 프로세스 별 시간 계산 함수
void SJF_Process_Time(vector<Process>& p) {
    int current_time = 0; // 현재까지 누적 시간을 저장할 변수
    vector<Process> result; // 실행된 순서대로 프로세스를 저장할 벡터

    while (result.size() < p.size()) {
        // 도착 시간이 현재 시간보다 작거나 같은 프로세스 중 실행 시간이 가장 짧은 프로세스 선택
        auto it = min_element(p.begin(), p.end(), [current_time](const Process& a, const Process& b) {
            if (a.completed) return false;
            if (b.completed) return true;
            if (a.at > current_time && b.at > current_time) return a.at < b.at;
            if (a.at > current_time) return false;
            if (b.at > current_time) return true;
            return a.rt < b.rt;
            });

        if (it->at > current_time) {
            current_time = it->at; // 현재 시간 갱신
        }

        it->wt = current_time - it->at; // 대기 시간 계산
        current_time += it->rt; // 현재 시간 갱신
        it->return_time = current_time; // 반환 시간 갱신
        it->tt = it->return_time - it->at; // 소요 시간 갱신
        it->response_time = it->wt; // 응답 시간 갱신
        it->completed = true; // 완료 상태 갱신
        result.push_back(*it); // 실행된 프로세스를 결과 벡터에 추가
    }

    // 결과 벡터를 원래 벡터에 복사
    p = result;
}

// SJF 스케줄링 함수
void SJF_Scheduling(vector<Process>& p) {
    cout << "\tSJF" << endl;
    int total_waiting_time = 0;
    int total_turnAround_time = 0;
    int total_response_time = 0;

    vector<GanttBlock> gantt_chart;

    // SJF 스케줄링 알고리즘 적용
    SJF_Process_Time(p);

    int current_time = 0;

    for (size_t i = 0; i < p.size(); i++) {
        // 현재 시간이 도착 시간보다 작으면 도착 시간으로 이동
        if (current_time < p[i].at) {
            current_time = p[i].at;
        }

        // 프로세스의 반환 시간 계산
        p[i].return_time = current_time + p[i].rt;

        // 간트 차트에 추가
        gantt_chart.push_back({ p[i].id, current_time, p[i].return_time });

        // 프로세스의 응답 시간, 대기 시간, 소요 시간 계산
        p[i].response_time = current_time - p[i].at;
        p[i].wt = p[i].response_time;
        p[i].tt = p[i].return_time - p[i].at;

        // 총 대기 시간, 반환 시간, 소요 시간을 누적
        total_waiting_time += p[i].wt;
        total_turnAround_time += p[i].tt;
        total_response_time += p[i].response_time;

        // 현재 시간을 프로세스가 종료된 시간으로 업데이트
        current_time = p[i].return_time;
    }

    // 간트 차트와 테이블 출력
    print_gantt_chart(gantt_chart);
    view_table(p);

    // 평균 대기 시간, 반환 시간, 소요 시간 출력
    cout << endl;
    cout << "Average Total Waiting time = " << fixed << setprecision(2) << (double)total_waiting_time / (double)p.size() << endl;
    cout << "Average Total turnAround time = " << fixed << setprecision(2) << (double)total_turnAround_time / (double)p.size() << endl;
    cout << "Average Total Response time = " << fixed << setprecision(2) << (double)total_response_time / (double)p.size() << endl;
}


#endif // SJF_H
