#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

// Define the Process structure
struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time of the process
    int burstTime;     // Burst time of the process
    int priority;      // Priority of the process (for Priority Scheduling)
    int waitingTime;   // Waiting time
    int turnaroundTime;// Turnaround time
};

// First Come First Serve (FCFS) Scheduling Algorithm
void fcfs(std::vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }

    std::cout << "\nFCFS Scheduling\n";
    std::cout << "PID\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        std::cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
                  << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }
}

// Shortest Job First (SJF) Scheduling Algorithm
bool compareBurstTime(Process p1, Process p2) {
    return p1.burstTime < p2.burstTime;
}

void sjf(std::vector<Process>& processes) {
    int n = processes.size();
    std::sort(processes.begin(), processes.end(), compareBurstTime);
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }

    std::cout << "\nSJF Scheduling\n";
    std::cout << "PID\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        std::cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
                  << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }
}

// Priority Scheduling Algorithm
bool comparePriority(Process p1, Process p2) {
    return p1.priority < p2.priority;
}

void priorityScheduling(std::vector<Process>& processes) {
    int n = processes.size();
    std::sort(processes.begin(), processes.end(), comparePriority);
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }

    std::cout << "\nPriority Scheduling\n";
    std::cout << "PID\tPriority\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        std::cout << p.pid << "\t" << p.priority << "\t\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
                  << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }
}

// Round Robin Scheduling Algorithm
void roundRobin(std::vector<Process>& processes, int quantum) {
    std::queue<Process> readyQueue;
    int currentTime = 0;
    int n = processes.size();
    std::vector<int> remainingBurstTime(n);

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = processes[i].burstTime;
    }

    std::cout << "\nRound Robin Scheduling (Quantum = " << quantum << ")\n";
    std::cout << "PID\tArrival\tBurst\tWaiting\tTurnaround\n";

    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (remainingBurstTime[i] > 0) {
                done = false; // There is a pending process

                if (remainingBurstTime[i] > quantum) {
                    currentTime += quantum;
                    remainingBurstTime[i] -= quantum;
                } else {
                    currentTime += remainingBurstTime[i];
                    processes[i].waitingTime = currentTime - processes[i].burstTime - processes[i].arrivalTime;
                    processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
                    remainingBurstTime[i] = 0;
                }
            }
        }

        // If all processes are done, exit the loop
        if (done) break;
    }

    // Display results
    for (const auto& p : processes) {
        std::cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
                  << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }
}

// Main Program
int main() {
    std::vector<Process> processes = {
        {1, 0, 8, 2, 0, 0},
        {2, 1, 4, 1, 0, 0},
        {3, 2, 9, 3, 0, 0},
        {4, 3, 5, 4, 0, 0},
    };

    int choice, quantum;
    std::cout << "Choose Scheduling Algorithm: \n";
    std::cout << "1. FCFS\n";
    std::cout << "2. SJF\n";
    std::cout << "3. Priority Scheduling\n";
    std::cout << "4. Round Robin\n";
    std::cin >> choice;

    switch(choice) {
        case 1:
            fcfs(processes);
            break;
        case 2:
            sjf(processes);
            break;
        case 3:
            priorityScheduling(processes);
            break;
        case 4:
            std::cout << "Enter Quantum Time: ";
            std::cin >> quantum;
            roundRobin(processes, quantum);
            break;
        default:
            std::cout << "Invalid choice!";
    }

    return 0;
}
