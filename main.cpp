#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "FCFS.h"
#include "SJF.h"
#include "NPP.h"
#include "PP.h"
#include "RR.h"
#include "Process.h"
#include "Gantt_chart.h"
#include "Function_To_Sorting.h"
#include "SRT.h"
#include "HRN.h"
#pragma warning(disable:4996)
using namespace std;

int main() {
    int process_count = 0; // 프로세스 개수를 저장할 변수
    Quantum quantum; // RR 스케줄링을 위한 시간 할당량

    // 입력 파일 열기
    ifstream inputFile("process.txt");
    if (!inputFile) {
        cerr << "File Open Fail" << endl;
        exit(1); // 파일 열기 실패 시 프로그램 종료
    }

    inputFile >> process_count; // 프로세스 개수 읽기

    vector<Process> process(process_count); // 프로세스 벡터 초기화

    // 메모리 할당 실패 확인
    if (process.empty()) {
        cerr << "메모리 할당 실패" << endl;
        exit(1); // 메모리 할당 실패 시 프로그램 종료
    }

    // 프로세스 정보 읽기
    for (int i = 0; i < process_count; i++) {
        inputFile >> process[i].id >> process[i].at >> process[i].rt >> process[i].priority;
    }

    inputFile >> quantum; // 시간 할당량 읽기

    inputFile.close(); // 입력 파일 닫기

    // 각 스케줄링 알고리즘 호출
    FCFS_Scheduling(process);
    cout << endl;
    SJF_Scheduling(process);
    cout << endl;
    NPP_Scheduling(process);
    cout << endl;
    PP_Scheduling(process);
    cout << endl;
    RR_Scheduling(process, quantum);
    cout << endl;
    SRT_Scheduling(process);
    cout << endl;
    HRN_Scheduling(process);
    cout << endl;

    return 0; 
}
