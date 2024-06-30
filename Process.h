#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
// Process 구조체 정의
struct Process {
    std::string id;        // 프로세스 ID
    int wt;                // 대기 시간
    int at;                // 도착 시간
    int rt;                // 실행 시간
    int priority;          // 우선순위
    int response_time;     // 응답 시간
    int return_time;       // 반환 시간
    int tt;                // 소요 시간
    bool completed;        // 완료 여부

    // Process 구조체의 기본 생성자
    Process() : wt(0), at(0), rt(0), priority(0), response_time(-1), return_time(0), tt(0), completed(false) {}
};

// Quantum 타입 정의
typedef int Quantum; // 시간 할당량

// 프로세스 벡터를 도착 시간(at) 기준으로 정렬하는 함수
void Process_init(std::vector<Process>& p) {
    std::sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
        });
}

#endif // PROCESS_H
