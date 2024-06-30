#ifndef GANTT_CHART_H
#define GANTT_CHART_H

#include "Process.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

// GanttBlock ����ü ����
// ��Ʈ ��Ʈ�� �� ����� ��Ÿ���� ����ü��, ���μ��� ID, ���� �ð�, ���� �ð��� �����Ѵ�.
struct GanttBlock {
    std::string pid;     // ���μ��� ID
    int start_time;      // ���� �ð�
    int end_time;        // ���� �ð�
};

// ��Ʈ ��Ʈ�� ����ϴ� �Լ�
void print_gantt_chart(const std::vector<GanttBlock>& gantt_chart) {
    // ���� �� ���μ��� ID �Ǵ� �ð��� ����Ͽ� �� ����� �ʿ��� �ʺ� ����Ѵ�.
    size_t max_pid_length = 0;
    for (const auto& block : gantt_chart) {
        max_pid_length = std::max(max_pid_length, block.pid.length());
    }
    size_t max_time_length = 0;
    for (const auto& block : gantt_chart) {
        max_time_length = std::max(max_time_length, std::to_string(block.end_time).length());
    }

    const size_t block_width = std::max(max_pid_length, max_time_length) + 2; // �е� �߰�

    // ��� ��� ���
    std::cout << "��";
    for (size_t i = 0; i < gantt_chart.size(); ++i) {
        std::cout << std::string(block_width, '-') << (i < gantt_chart.size() - 1 ? "��" : "��");
    }
    std::cout << "\n";

    // ���μ��� ID ���
    std::cout << "��";
    for (const auto& block : gantt_chart) {
        int padding = (block_width - block.pid.length()) / 2;
        std::cout << std::string(padding, ' ') << block.pid << std::string(block_width - padding - block.pid.length(), ' ') << "��";
    }
    std::cout << "\n";

    // �߰� ��� ���
    std::cout << "��";
    for (size_t i = 0; i < gantt_chart.size(); ++i) {
        std::cout << std::string(block_width, '-') << (i < gantt_chart.size() - 1 ? "��" : "��");
    }
    std::cout << "\n";

    // �ð� ���
    for (size_t i = 0; i < gantt_chart.size(); ++i) {
        std::cout << std::setw(block_width) << std::right << gantt_chart[i].start_time;
    }
    std::cout << std::setw(block_width) << std::right << gantt_chart.back().end_time << "\n";

    // �ϴ� ��� ���
    std::cout << "��";
    for (size_t i = 0; i < gantt_chart.size(); ++i) {
        std::cout << std::string(block_width, '-') << (i < gantt_chart.size() - 1 ? "��" : "��");
    }
    std::cout << "\n";
}

#endif // GANTT_CHART_H
