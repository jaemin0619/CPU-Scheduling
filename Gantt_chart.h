#ifndef GANTT_CHART_H
#define GANTT_CHART_H

#include "Process.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

// GanttBlock 구조체 정의
// 간트 차트의 각 블록을 나타내는 구조체로, 프로세스 ID, 시작 시간, 종료 시간을 포함한다.
struct GanttBlock {
    std::string pid;     // 프로세스 ID
    int start_time;      // 시작 시간
    int end_time;        // 종료 시간
};

// 간트 차트를 출력하는 함수
void print_gantt_chart(const std::vector<GanttBlock>& gantt_chart) {
    // 가장 긴 프로세스 ID 또는 시간에 기반하여 각 블록의 필요한 너비를 계산한다.
    size_t max_pid_length = 0;
    for (const auto& block : gantt_chart) {
        max_pid_length = std::max(max_pid_length, block.pid.length());
    }
    size_t max_time_length = 0;
    for (const auto& block : gantt_chart) {
        max_time_length = std::max(max_time_length, std::to_string(block.end_time).length());
    }

    const size_t block_width = std::max(max_pid_length, max_time_length) + 2; // 패딩 추가

    // 상단 경계 출력
    std::cout << "┌";
    for (size_t i = 0; i < gantt_chart.size(); ++i) {
        std::cout << std::string(block_width, '-') << (i < gantt_chart.size() - 1 ? "┬" : "┐");
    }
    std::cout << "\n";

    // 프로세스 ID 출력
    std::cout << "│";
    for (const auto& block : gantt_chart) {
        int padding = (block_width - block.pid.length()) / 2;
        std::cout << std::string(padding, ' ') << block.pid << std::string(block_width - padding - block.pid.length(), ' ') << "│";
    }
    std::cout << "\n";

    // 중간 경계 출력
    std::cout << "├";
    for (size_t i = 0; i < gantt_chart.size(); ++i) {
        std::cout << std::string(block_width, '-') << (i < gantt_chart.size() - 1 ? "┼" : "┤");
    }
    std::cout << "\n";

    // 시간 출력
    for (size_t i = 0; i < gantt_chart.size(); ++i) {
        std::cout << std::setw(block_width) << std::right << gantt_chart[i].start_time;
    }
    std::cout << std::setw(block_width) << std::right << gantt_chart.back().end_time << "\n";

    // 하단 경계 출력
    std::cout << "└";
    for (size_t i = 0; i < gantt_chart.size(); ++i) {
        std::cout << std::string(block_width, '-') << (i < gantt_chart.size() - 1 ? "┴" : "┘");
    }
    std::cout << "\n";
}

#endif // GANTT_CHART_H
