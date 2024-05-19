#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

// 프로세스 구조체 정의
struct Process {
    int id;               // 프로세스 식별자
    int arrivalTime;      // 도착 시간
    int burstTime;        // 실행 시간
    int remainingTime;    // 남은 실행 시간
    int startTime;        // 시작 시간
    int endTime;          // 종료 시간
    int waitingTime;      // 대기 시간
    int turnaroundTime;   // 전체 소요 시간
    int responseTime;     // 응답 시간
};

// 프로세서 구조체 정의
struct Processor {
    int id;               // 프로세서 식별자
    bool isIdle;          // 프로세서가 현재 작업 중인지 여부
    Process* runningProcess;  // 현재 실행 중인 프로세스 포인터
};

// 표의 헤더를 출력하는 함수
void printTableHeader() {
    cout << setw(10) << "Process";
    cout << setw(15) << "Arrival Time";
    cout << setw(15) << "Burst Time";
    cout << setw(15) << "Waiting Time";
    cout << setw(15) << "Response Time" << endl;
    cout << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
}

// 각 프로세스의 상세 정보를 출력하는 함수
void printProcessDetails(const Process& p) {
    cout << setw(10) << p.id;
    cout << setw(15) << p.arrivalTime;
    cout << setw(15) << p.burstTime;
    cout << setw(15) << p.waitingTime;
    cout << setw(15) << p.responseTime << endl;
}

// 성능 지표를 계산하는 함수
void calculateMetrics(const vector<Process>& processes, double& avgTurnaroundTime, double& avgWaitingTime, double& avgResponseTime, double& cpuUtilization, double& throughput) {
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    int totalResponseTime = 0;
    int totalExecutedProcesses = 0;

    // 각 프로세스의 성능 지표 누적 계산
    for (const Process& p : processes) {
        totalTurnaroundTime += p.turnaroundTime;
        totalWaitingTime += p.waitingTime;
        totalResponseTime += p.responseTime;
        if (p.endTime > 0) {
            totalExecutedProcesses++;
        }
    }

    // 평균 성능 지표 계산
    avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / totalExecutedProcesses;
    avgWaitingTime = static_cast<double>(totalWaitingTime) / totalExecutedProcesses;
    avgResponseTime = static_cast<double>(totalResponseTime) / totalExecutedProcesses;
    cpuUtilization = static_cast<double>(totalExecutedProcesses) / processes.size();
    throughput = static_cast<double>(totalExecutedProcesses) / totalTurnaroundTime;
}

int main() {
    // 사용자로부터 프로세서의 개수 입력 받기
    int numProcessors;
    cout << "사용할 프로세서의 수를 입력하세요: ";
    cin >> numProcessors;

    // 프로세서 벡터 생성 및 초기화
    vector<Processor> processors(numProcessors, {0, true, nullptr});

    // 사용자로부터 프로세스의 개수 입력 받기
    int numProcesses;
    cout << "프로세스의 수를 입력하세요: ";
    cin >> numProcesses;

    // 프로세스 벡터 생성 및 초기화
    vector<Process> processes(numProcesses);
    for (int i = 0; i < numProcesses; ++i) {
        processes[i].id = i + 1;
        cout << "arrival time을 입력하세요: " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "burst time을 입력하세요: " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // 도착 시간에 따라 프로세스 정렬
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // 현재 시간 초기화
    int currentTime = 0;
    queue<Process*> readyQueue;

    // 표의 헤더 출력
    printTableHeader();

    // 스케줄링 루프
    while (true) {
        // 프로세서에 할당 가능한 프로세스가 있으면 할당
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

        // 모든 프로세스가 실행되었는지 확인
        bool allProcessesExecuted = all_of(processes.begin(), processes.end(), [](const Process& p) {
            return p.remainingTime == 0;
        });

        if (allProcessesExecuted) {
            break;
        }

        // 도착한 프로세스 큐에 삽입
        for (Process& process : processes) {
            if (process.arrivalTime == currentTime && process.remainingTime > 0) {
                readyQueue.push(&process);
            }
        }

        // 실행 중인 각 프로세스에 대해 1타임 유닛 소모
        for (Processor& processor : processors) {
            if (!processor.isIdle) {
                processor.runningProcess->remainingTime--;
                if (processor.runningProcess->remainingTime == 0) {
                    // 프로세스 실행 완료 시간 설정
                    processor.isIdle = true;
                    processor.runningProcess->endTime = currentTime + 1;
                    processor.runningProcess->turnaroundTime = processor.runningProcess->endTime - processor.runningProcess->arrivalTime;
                    processor.runningProcess->waitingTime = processor.runningProcess->turnaroundTime - processor.runningProcess->burstTime;

                    // 프로세스 상세 정보 출력
                    printProcessDetails(*processor.runningProcess);
                }
            }
        }

        // 현재 시간 증가
        currentTime++;
    }

    // 성능 지표 계산 및 출력
    double avgTurnaroundTime, avgWaitingTime, avgResponseTime, cpuUtilization, throughput;
    calculateMetrics(processes, avgTurnaroundTime, avgWaitingTime, avgResponseTime, cpuUtilization, throughput);

    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Response Time: " << avgResponseTime << endl;
    cout << "CPU Utilization: " << cpuUtilization * 100 << "%" << endl;
    cout << "Throughput: " << throughput << endl;

    return 0;
}
