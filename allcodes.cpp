

// ROUND ROBIN+++++++++++++++++++++

#include <iostream>
using namespace std;

void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum)
{
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];
    int t = 0;

    while (1)
    {
        bool done = true;
        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = false;
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true)
            break;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n, int bt[], int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);

    cout << "PN\t "
         << " \tBT "
         << " WT "
         << " \tTAT\n";
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << " " << i + 1 << "\t\t" << bt[i] << "\t " << wt[i] << "\t\t " << tat[i] << endl;
    }

    cout << "Average waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}

int main()
{
    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = {10, 5, 8};
    int quantum = 2;
    findavgTime(processes, n, burst_time, quantum);
    return 0;
}

// Priority Scheduling with premption+++++++++++++++++++++

#include <stdio.h>
#define MIN -9999

struct proc
{
    int no, at, bt, rt, ct, wt, tat, pri, temp;
};

// Function to read process details
struct proc read(int i)
{
    struct proc p;
    printf("\nProcess No: %d\n", i);
    p.no = i;
    printf("Enter Arrival Time: ");
    scanf("%d", &p.at);
    printf("Enter Burst Time: ");
    scanf("%d", &p.bt);
    p.rt = p.bt;
    printf("Enter Priority: ");
    scanf("%d", &p.pri);
    p.temp = p.pri; // Store initial priority in temp
    return p;
}

int main()
{
    int i, n, c, remaining, max_val, max_index;
    struct proc p[10], temp;
    float avgtat = 0, avgwt = 0;
    printf("<-- Highest Priority First Scheduling Algorithm (Preemptive) -->\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    // Read process details
    for (int i = 0; i < n; i++)
        p[i] = read(i + 1);

    remaining = n;

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

    // Initialize max priority process
    max_val = p[0].temp, max_index = 0;

    // Find the process with maximum priority among arrived processes
    for (int j = 0; j < n && p[j].at <= p[0].at; j++)
        if (p[j].temp > max_val)
            max_val = p[j].temp, max_index = j;

    i = max_index;
    c = p[i].ct = p[i].at + 1;
    p[i].rt--;

    if (p[i].rt == 0)
    {
        p[i].temp = MIN;
        remaining--;
    }

    // Perform scheduling until all processes are executed
    while (remaining > 0)
    {
        max_val = p[0].temp, max_index = 0;

        // Find the process with maximum priority among arrived processes
        for (int j = 0; j < n && p[j].at <= c; j++)
            if (p[j].temp > max_val)
                max_val = p[j].temp, max_index = j;

        i = max_index;
        p[i].ct = c = c + 1;
        p[i].rt--;

        if (p[i].rt == 0)
        {
            p[i].temp = MIN;
            remaining--;
        }
    }

    // Print process details
    printf("\nProcessNo\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        avgtat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        avgwt += p[i].wt;
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
    }

    // Calculate and print average turnaround time and average waiting time
    avgtat /= n;
    avgwt /= n;
    printf("\nAverage TurnAroundTime = %f\nAverage WaitingTime = %f", avgtat, avgwt);

    return 0;
}

// Priority Scheduling without premption+++++++++++++++++++++

#include <iostream>
using namespace std;

int main()
{
    int n = 5;       // Number of Processes
    int CPU = 0;     // CPU Current time
    int allTime = 0; // Time needed to finish all processes

    int arrivaltime[n] = {0, 5, 12, 2, 9};
    int bursttime[n] = {11, 28, 2, 10, 16};
    int priority[n] = {2, 0, 3, 1, 4};
    int ATt[n];
    int NoP = n; // number of Processes
    int PPt[n];
    int waitingTime[n];
    int turnaroundTime[n];
    int i = 0;

    for (i = 0; i < n; i++)
    {
        PPt[i] = priority[i];
        ATt[i] = arrivaltime[i];
    }

    int LAT = 0; // LastArrivalTime
    for (i = 0; i < n; i++)
        if (arrivaltime[i] > LAT)
            LAT = arrivaltime[i];

    int MAX_P = 0; // Max Priority
    for (i = 0; i < n; i++)
        if (PPt[i] > MAX_P)
            MAX_P = PPt[i];

    int ATi = 0;     // Pointing to Arrival Time indix
    int P1 = PPt[0]; // Pointing to 1st priority Value
    int P2 = PPt[0]; // Pointing to 2nd priority Value

    // finding the First Arrival Time and Highest priority Process
    int j = -1;
    while (NoP > 0 && CPU <= 1000)
    {
        for (i = 0; i < n; i++)
        {
            if ((ATt[i] <= CPU) && (ATt[i] != (LAT + 10)))
            {
                if (PPt[i] != (MAX_P + 1))
                {
                    P2 = PPt[i];
                    j = 1;

                    if (P2 < P1)
                    {
                        j = 1;
                        ATi = i;
                        P1 = PPt[i];
                        P2 = PPt[i];
                    }
                }
            }
        }

        if (j == -1)
        {
            CPU = CPU + 1;
            continue;
        }
        else
        {
            waitingTime[ATi] = CPU - ATt[ATi];
            CPU = CPU + bursttime[ATi];
            turnaroundTime[ATi] = CPU - ATt[ATi];
            ATt[ATi] = LAT + 10;
            j = -1;
            PPt[ATi] = MAX_P + 1;
            ATi = 0;        // Pointing to Arrival Time index
            P1 = MAX_P + 1; // Pointing to 1st priority Value
            P2 = MAX_P + 1; // Pointing to 2nd priority Value
            NoP = NoP - 1;
        }
    }

    cout << "\nProcess_Number\tBurst_Time\tPriority\tArrival_Time\tWaiting_Time\tTurnaround_Time\n\n";
    for (i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << "\t\t" << bursttime[i] << "\t\t" << priority[i] << "\t\t" << arrivaltime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
    }

    float AvgWT = 0;  // Average waiting time
    float AVGTaT = 0; // Average Turn around time
    for (i = 0; i < n; i++)
    {
        AvgWT = waitingTime[i] + AvgWT;
        AVGTaT = turnaroundTime[i] + AVGTaT;
    }

    cout << "Average waiting time = " << AvgWT / n << endl;
    cout << "Average turnaround time = " << AVGTaT / n << endl;
}

// SRTF with preemption ++++++++++++++++++++++++++

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process
{
    int pid;           // Process ID
    int arrivalTime;   // Arrival Time
    int burstTime;     // Burst Time
    int remainingTime; // Remaining Burst Time
};

bool sortByArrival(Process a, Process b)
{
    return a.arrivalTime < b.arrivalTime;
}

bool sortByRemainingTime(Process a, Process b)
{
    return a.remainingTime < b.remainingTime;
}

int main()
{
    int n; // Number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Take input for arrival time and burst time
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Sort the processes by arrival time
    sort(processes.begin(), processes.end(), sortByArrival);

    int currentTime = 0;               // Current time
    vector<Process> readyQueue;        // Ready queue
    vector<int> waitingTimes(n, 0);    // Waiting times of processes
    vector<int> turnaroundTimes(n, 0); // Turnaround times of processes

    while (!readyQueue.empty() || !processes.empty())
    {
        // Add new arrivals to the ready queue
        while (!processes.empty() && processes.front().arrivalTime <= currentTime)
        {
            readyQueue.push_back(processes.front());
            processes.erase(processes.begin());
        }

        // Sort the ready queue by remaining burst time
        sort(readyQueue.begin(), readyQueue.end(), sortByRemainingTime);

        if (!readyQueue.empty())
        {
            Process &shortestJob = readyQueue.front();
            shortestJob.remainingTime--;
            currentTime++;

            // If the shortest job is completed
            if (shortestJob.remainingTime == 0)
            {
                turnaroundTimes[shortestJob.pid - 1] = currentTime - shortestJob.arrivalTime;
                waitingTimes[shortestJob.pid - 1] = turnaroundTimes[shortestJob.pid - 1] - shortestJob.burstTime;
                readyQueue.erase(readyQueue.begin());
            }
        }
        else
        {
            currentTime++;
        }
    }

    // Calculate average waiting time and average turnaround time
    double avgWaitingTime = 0.0, avgTurnaroundTime = 0.0;
    for (int i = 0; i < n; i++)
    {
        avgWaitingTime += waitingTimes[i];
        avgTurnaroundTime += turnaroundTimes[i];
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    // Print the results
    cout << setw(10) << "Process" << setw(15) << "Waiting Time" << setw(20) << "Turnaround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(10) << i + 1 << setw(15) << waitingTimes[i] << setw(20) << turnaroundTimes[i] << endl;
    }
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    return 0;
}

// SJF without preemption+++++++++++++++++++

#include <iostream>
#include <climits>
using namespace std;

void printdata(int at[], int bt[], int ct[], int n)
{
    cout << "AT"
         << "\t\t"
         << "BT"
         << "\t\t"
         << "CT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << at[i] << "\t\t" << bt[i] << "\t\t" << ct[i] << endl;
    }
}

int main()
{
    int at[6] = {6, 3, 4, 1, 2, 5};
    int bt[6] = {1, 3, 6, 5, 2, 1};

    int n = sizeof at / sizeof at[0];

    // sorting of given data
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (at[j] < at[i])
            {
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
            }
        }
    }
    bool executed[n];
    int currTime = 0;
    int ct[n];
    ct[0] = bt[0] + at[0];
    executed[0] = true;
    currTime = bt[0];

    for (int j = 0; j < n; j++)
    {
        int minBt = INT_MAX;
        int foundAt = -1;
        for (int i = 1; i < n; i++)
        {
            if (!executed[i] && at[i] <= currTime && bt[i] < minBt)
            {
                minBt = bt[i];
                foundAt = i;
            }
        }
        executed[foundAt] = true;
        currTime += bt[foundAt];
        ct[foundAt] = currTime + 1;
    }

    printdata(at, bt, ct, n);

    return 0;
}

// FCFS++++++++++++++++++++++++++++

#include <iostream>
using namespace std;

void CalculateWaitingTime(int at[], int bt[], int N)
{
    // finding completion time:-

    int ct[N];
    ct[0] = bt[0];
    for (int i = 1; i < N; i++)
    {
        ct[i] = ct[i - 1] + bt[i];
    }

    // finding waiting time

    int wt[N];
    for (int i = 0; i < N; i++)
    {
        wt[i] = ct[i] - at[i] - bt[i];
    }

    // printing the values

    cout << "PN\t\tAT\t\t"
         << "BT\t\tWT\n\n";
    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << wt[i] << endl;
    }
    float sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += wt[i];
    }
    cout << "Average waiting time = " << sum / N << endl;
}

int main()
{

    int N = 5;

    int at[] = {0, 1, 2, 3, 4};

    int bt[] = {4, 3, 1, 2, 5};

    CalculateWaitingTime(at, bt, N);
    return 0;
}

// ⁠Petersons solution for Critical Section Problem++++++++++++++++++++++++

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>

const int BSIZE = 8;
const int PWT = 1000;
const int CWT = 4000;
const int RT = 30000;

bool shmid1 = false;
int shmid2 = 0;
std::vector<int> shmid3(BSIZE, 0);
int shmid4 = 0;

int state = 1;

int myrand(int n)
{
    return rand() % n + 1;
}

void producer()
{
    while (state == 1)
    {
        shmid1 = true;
        std::cout << "Producer is ready now.\n";
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));

        shmid2 = 0;
        while (shmid1 && shmid2 == 0)
        {
        }

        // Critical Section Begin
        int index = 0;
        while (index < BSIZE)
        {
            if (shmid3[index] == 0)
            {
                const int tempo = myrand(BSIZE * 3);
                std::cout << "Job " << tempo << " has been produced\n";
                shmid3[index] = tempo;
                break;
            }
            index++;
        }
        if (index == BSIZE)
        {
            std::cout << "Buffer is full, nothing can be produced!!!\n";
        }
        std::cout << "Buffer: ";
        for (int val : shmid3)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";
        // Critical Section End

        shmid1 = false;
        if (state == 0)
            break;
        const int wait_time = myrand(PWT);
        std::cout << "Producer will wait for " << wait_time / 1000.0 << " seconds\n";
        // std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
    }
}

void consumer()
{
    shmid1 = false;
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    while (state == 1)
    {
        shmid1 = true;
        std::cout << "Consumer is ready now.\n";
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));

        shmid2 = 1;
        while (shmid1 && shmid2 == 1)
        {
        }

        // Critical Section Begin
        if (shmid3[0] != 0)
        {
            std::cout << "Job " << shmid3[0] << " has been consumed\n";
            shmid3[0] = 0;
            int index = 1;
            while (index < BSIZE)
            {
                shmid3[index - 1] = shmid3[index];
                index++;
            }
            shmid3[index - 1] = 0;
        }
        else
        {
            std::cout << "Buffer is empty, nothing can be consumed!!!\n";
        }
        std::cout << "Buffer: ";
        for (int val : shmid3)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";
        // Critical Section End

        shmid1 = false;
        if (state == 0)
            break;
        const int wait_time = myrand(CWT);
        std::cout << "Consumer will sleep for " << wait_time / 1000.0 << " seconds\n";
        // std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
    }
}

int main()
{
    srand(time(nullptr));

    // Start producer and consumer in separate threads (simulated)
    // std::thread producer_thread(producer);
    // std::thread consumer_thread(consumer);

    // Simulate program run for RT milliseconds
    for (int elapsed_time = 0; elapsed_time < RT; elapsed_time += 100)
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Set state to 0 to stop producer and consumer
    state = 0;

    // Join threads
    // producer_thread.join();
    // consumer_thread.join();

    std::cout << "The clock ran out.\n";

    return 0;
}

// #2 only method

#include <iostream>
#include <vector>

const int N = 2; // Number of threads (producer and consumer)

std::vector<bool> flag(N, false); // Flags to indicate readiness
int turn = 0;                     // Variable to indicate turn

void producer(int j)
{
    do
    {
        flag[j] = true; // Producer j is ready to produce
        turn = 1 - j;   // Allow consumer to consume
        while (flag[1 - j] && turn == 1 - j)
        {
            // Wait for consumer to finish
            // Producer waits if consumer is ready and it's consumer's turn
        }

        // Critical Section: Producer produces an item and puts it into the buffer

        flag[j] = false; // Producer is out of the critical section

        // Remainder Section: Additional actions after critical section
    } while (true); // Continue indefinitely
}

void consumer(int i)
{
    do
    {
        flag[i] = true; // Consumer i is ready to consume
        turn = i;       // Allow producer to produce
        while (flag[1 - i] && turn == i)
        {
            // Wait for producer to finish
            // Consumer waits if producer is ready and it's producer's turn
        }

        // Critical Section: Consumer consumes an item from the buffer

        flag[i] = false; // Consumer is out of the critical section

        // Remainder Section: Additional actions after critical section
    } while (true); // Continue indefinitely
}

int main()
{

    return 0;
}