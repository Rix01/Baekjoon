#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

// ���μ��� ����ü ����
struct Process {
    int id;               // ���μ��� �ĺ���
    int arrivalTime;      // ���� �ð�
    int burstTime;        // ���� �ð�
    int remainingTime;    // ���� ���� �ð�
    int startTime;        // ���� �ð�
    int endTime;          // ���� �ð�
    int waitingTime;      // ��� �ð�
    int turnaroundTime;   // ��ü �ҿ� �ð�
    int responseTime;     // ���� �ð�
};

// ���μ��� ����ü ����
struct Processor {
    int id;               // ���μ��� �ĺ���
    bool isIdle;          // ���μ����� ���� �۾� ������ ����
    Process* runningProcess;  // ���� ���� ���� ���μ��� ������
};

// ǥ�� ����� ����ϴ� �Լ�
void printTableHeader() {
    cout << setw(10) << "Process";
    cout << setw(15) << "Arrival Time";
    cout << setw(15) << "Burst Time";
    cout << setw(15) << "Waiting Time";
    cout << setw(15) << "Response Time" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
}

// �� ���μ����� �� ������ ����ϴ� �Լ�
void printProcessDetails(const Process& p) {
    cout << setw(10) << p.id;
    cout << setw(15) << p.arrivalTime;
    cout << setw(15) << p.burstTime;
    cout << setw(15) << p.waitingTime;
    cout << setw(15) << p.responseTime << endl;
}

// ���� ��ǥ�� ����ϴ� �Լ�
void calculateMetrics(const vector<Process>& processes, double& avgTurnaroundTime, double& avgWaitingTime, double& avgResponseTime, double& cpuUtilization, double& throughput) {
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    int totalResponseTime = 0;
    int totalExecutedProcesses = 0;

    // �� ���μ����� ���� ��ǥ ���� ���
    for (const Process& p : processes) {
        totalTurnaroundTime += p.turnaroundTime;
        totalWaitingTime += p.waitingTime;
        totalResponseTime += p.responseTime;
        if (p.endTime > 0) {
            totalExecutedProcesses++;
        }
    }

    // ��� ���� ��ǥ ���
    avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / totalExecutedProcesses;
    avgWaitingTime = static_cast<double>(totalWaitingTime) / totalExecutedProcesses;
    avgResponseTime = static_cast<double>(totalResponseTime) / totalExecutedProcesses;
    cpuUtilization = static_cast<double>(totalExecutedProcesses) / processes.size();
    throughput = static_cast<double>(totalExecutedProcesses) / totalTurnaroundTime;
}

int main() {
    // ����ڷκ��� ���μ����� ���� �Է� �ޱ�
    int numProcessors;
    cout << "����� ���μ����� ���� �Է��ϼ���: ";
    cin >> numProcessors;

    // ���μ��� ���� ���� �� �ʱ�ȭ
    vector<Processor> processors(numProcessors, {0, true, nullptr});

    // ����ڷκ��� ���μ����� ���� �Է� �ޱ�
    int numProcesses;
    cout << "���μ����� ���� �Է��ϼ���: ";
    cin >> numProcesses;

    // ���μ��� ���� ���� �� �ʱ�ȭ
    vector<Process> processes(numProcesses);
    for (int i = 0; i < numProcesses; ++i) {
        processes[i].id = i + 1;
        cout << "arrival time�� �Է��ϼ���: " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "burst time�� �Է��ϼ���: " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // ���� �ð��� ���� ���μ��� ����
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // ���� �ð� �ʱ�ȭ
    int currentTime = 0;
    queue<Process*> readyQueue;

    // ǥ�� ��� ���
    printTableHeader();

    // �����ٸ� ����
    while (true) {
        // ���μ����� �Ҵ� ������ ���μ����� ������ �Ҵ�
        for (Processor& processor : processors) {
            if (processor.isIdle && !readyQueue.empty()) {
                Process* nextProcess = readyQueue.front();
                readyQueue.pop();
                processor.isIdle = false;
                processor.runningProcess = nextProcess;
                nextProcess->startTime = currentTime;
                nextProcess->responseTime = currentTime - nextProcess->arrivalTime;
                break;
            }
        }

        // ��� ���μ����� ����Ǿ����� Ȯ��
        bool allProcessesExecuted = all_of(processes.begin(), processes.end(), [](const Process& p) {
            return p.remainingTime == 0;
        });

        if (allProcessesExecuted) {
            break;
        }

        // ������ ���μ��� ť�� ����
        for (Process& process : processes) {
            if (process.arrivalTime == currentTime && process.remainingTime > 0) {
                readyQueue.push(&process);
            }
        }

        // ���� ���� �� ���μ����� ���� 1Ÿ�� ���� �Ҹ�
        for (Processor& processor : processors) {
            if (!processor.isIdle) {
                processor.runningProcess->remainingTime--;
                if (processor.runningProcess->remainingTime == 0) {
                    // ���μ��� ���� �Ϸ� �ð� ����
                    processor.isIdle = true;
                    processor.runningProcess->endTime = currentTime + 1;
                    processor.runningProcess->turnaroundTime = processor.runningProcess->endTime - processor.runningProcess->arrivalTime;
                    processor.runningProcess->waitingTime = processor.runningProcess->turnaroundTime - processor.runningProcess->burstTime;

                    // ���μ��� �� ���� ���
                    printProcessDetails(*processor.runningProcess);
                }
            }
        }

        // ���� �ð� ����
        currentTime++;
    }

    // ���� ��ǥ ��� �� ���
    double avgTurnaroundTime, avgWaitingTime, avgResponseTime, cpuUtilization, throughput;
    calculateMetrics(processes, avgTurnaroundTime, avgWaitingTime, avgResponseTime, cpuUtilization, throughput);

    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Response Time: " << avgResponseTime << endl;
    cout << "CPU Utilization: " << cpuUtilization * 100 << "%" << endl;
    cout << "Throughput: " << throughput << endl;

    return 0;
}
