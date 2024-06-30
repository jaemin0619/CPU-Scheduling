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
    int process_count = 0; // ���μ��� ������ ������ ����
    Quantum quantum; // RR �����ٸ��� ���� �ð� �Ҵ緮

    // �Է� ���� ����
    ifstream inputFile("process.txt");
    if (!inputFile) {
        cerr << "File Open Fail" << endl;
        exit(1); // ���� ���� ���� �� ���α׷� ����
    }

    inputFile >> process_count; // ���μ��� ���� �б�

    vector<Process> process(process_count); // ���μ��� ���� �ʱ�ȭ

    // �޸� �Ҵ� ���� Ȯ��
    if (process.empty()) {
        cerr << "�޸� �Ҵ� ����" << endl;
        exit(1); // �޸� �Ҵ� ���� �� ���α׷� ����
    }

    // ���μ��� ���� �б�
    for (int i = 0; i < process_count; i++) {
        inputFile >> process[i].id >> process[i].at >> process[i].rt >> process[i].priority;
    }

    inputFile >> quantum; // �ð� �Ҵ緮 �б�

    inputFile.close(); // �Է� ���� �ݱ�

    // �� �����ٸ� �˰��� ȣ��
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
