#include<bits/stdc++.h>

using namespace std;

// FCFS
void fcfs()
{
    int num;
    cout << "Enter number of processes: ";
    cin >> num;

    string  process[num];
    int bt[num], wt[num], tat[num], sumWT = 0, sumTAT = 0;
    wt[0] = 0;
    tat[0] = bt[0];

    for (int i=0; i<num; i++)
    {
        cout << "Enter BT for process P" << i << ": ";
        cin >> bt[i];

        if (i > 0)
        {
            wt[i] = bt[i-1] + wt[i-1];
        }

        tat[i] = bt[i] + wt[i];

        sumWT += wt[i];
        sumTAT += tat[i];
    }

    cout << endl << "Processes are: " << endl << endl;

    cout << "Process \t BT" << endl;
    for (int i=0; i<num; i++)
    {
        cout << "   P" << i << "   \t" << bt[i] << "ms" << endl;
    }

    cout << endl << "WT and TAT Calculated: " << endl << endl;

    cout << "Process \t BT \t WT \t TAT" << endl;
    for (int i=0; i<num; i++)
    {
        cout << "   P" << i << "   \t";
        cout << bt[i] << "ms" << "\t";
        cout << wt[i] << "ms" << "\t";
        cout << tat[i] << "ms" << endl;
    }

    cout << endl;
    cout << "Average WT: " << sumWT/num << "ms" << endl;
    cout << "Average TAT: " << sumTAT/num << "ms" << endl;

}

// Non SJF
int mat[10][6];
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void arrangeArrival(int num, int mat[][6])
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num - i - 1; j++)
        {
            if (mat[j][1] > mat[j + 1][1])
            {
                for (int k = 0; k < 5; k++)
                {
                    swap(mat[j][k], mat[j + 1][k]);
                }
            }
        }
    }
}

void completionTime(int num, int mat[][6])
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];
    mat[0][5] = mat[0][3] - mat[0][1];
    mat[0][4] = mat[0][5] - mat[0][2];

    for (int i = 1; i < num; i++)
    {
        temp = mat[i - 1][3];
        int low = mat[i][2];
        for (int j = i; j < num; j++)
        {
            if (temp >= mat[j][1] && low >= mat[j][2])
            {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2];
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for (int k = 0; k < 6; k++)
        {
            swap(mat[val][k], mat[i][k]);
        }
    }
}

// Pre SJF

struct ProcessPreSJF
{
    int pid;
    int bt;
    int art;
};

void findWaitingTimePSJF(ProcessPreSJF proc[], int n,
                         int wt[])
{
    int rt[n];

    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((proc[j].art <= t) &&
                    (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false)
        {
            t++;
            continue;
        }

        rt[shortest]--;

        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (rt[shortest] == 0)
        {
            complete++;
            check = false;

            finish_time = t + 1;
            wt[shortest] = finish_time -
                           proc[shortest].bt -
                           proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}

void findTurnAroundTimePSJF(ProcessPreSJF proc[], int n,
                            int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

void findavgTimePSJF(ProcessPreSJF proc[], int n)
{
    int wt[n], tat[n], total_wt = 0,
                       total_tat = 0;

    findWaitingTimePSJF(proc, n, wt);
    findTurnAroundTimePSJF(proc, n, wt, tat);

    cout << "ProcessPreSJFes "
         << " Burst time "
         << " Waiting time "
         << " Turn around time\n";

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << proc[i].pid << "\t\t"
             << proc[i].bt << "\t\t " << wt[i]
             << "\t\t " << tat[i] << endl;
    }

    cout << "\nAverage waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}

// NPEPS
int totalprocessNPEPS;
struct processNPEPS
{
    int at,bt,pr,pno;
};

processNPEPS proc[50];


bool comp(processNPEPS a,processNPEPS b)
{
    if(a.at == b.at)
    {
        return a.pr<b.pr;
    }
    else
    {
        return a.at<b.at;
    }
}

void get_wt_time(int wt[])
{
    int service[50];

    service[0] = proc[0].at;
    wt[0]=0;


    for(int i=1; i<totalprocessNPEPS; i++)
    {
        service[i]=proc[i-1].bt+service[i-1];

        wt[i]=service[i]-proc[i].at;

        if(wt[i]<0)
        {
            wt[i]=0;
        }
    }

}

void get_tat_time(int tat[],int wt[])
{
    for(int i=0; i<totalprocessNPEPS; i++)
    {
        tat[i]=proc[i].bt+wt[i];
    }

}

void findgc()
{
    int wt[50],tat[50];

    double wavg=0,tavg=0;

    get_wt_time(wt);
    get_tat_time(tat,wt);

    int stime[50],ctime[50];

    stime[0] = proc[0].at;
    ctime[0]=stime[0]+tat[0];

    for(int i=1; i<totalprocessNPEPS; i++)
    {
        stime[i]=ctime[i-1];
        ctime[i]=stime[i]+tat[i]-wt[i];
    }

    cout<<"Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time"<<endl;

    for(int i=0; i<totalprocessNPEPS; i++)
    {
        wavg += wt[i];
        tavg += tat[i];

        cout<<proc[i].pno<<"\t\t"<<
            stime[i]<<"\t\t"<<ctime[i]<<"\t\t"<<
            tat[i]<<"\t\t\t"<<wt[i]<<endl;
    }

    cout<<"Average waiting time is : ";
    cout<<wavg/(float)totalprocessNPEPS<<endl;
    cout<<"average turnaround time : ";
    cout<<tavg/(float)totalprocessNPEPS<<endl;

}

// PEPS

struct processPEPS {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

void initPEPS() {
    int n;
    struct processPEPS p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: ";
    cin>>n;

    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        cout<<"Enter priority of the process "<<i+1<<": ";
        cin>>p[i].priority;
        p[i].pid = i+1;
        burst_remaining[i] = p[i].burst_time;
        cout<<endl;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time) {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;

            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;

    cout<<endl<<endl;

    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].priority<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].response_time<<"\t"<<"\n"<<endl;
    }
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
    cout<<"Average Response Time = "<<avg_response_time<<endl;
}

// ROUND ROBIN START

class Process
{
public:
    string processName;
    int burstTime, waitingTime, turnAroundTime, remainingTime;

    Process(string name, int bt)
    {
        processName = name;
        burstTime = bt;
        remainingTime = bt;
        waitingTime = 0;
        turnAroundTime = 0;
    }
};

class RoundRobin
{
public:
    int timeQuantum;
    vector<Process> processes;


    RoundRobin(int tq)
    {
        timeQuantum = tq;
    }

    void inputProcesses()
    {
        int n;
        cout << "Enter number of processes: " << endl;
        cin >> n;

        while (n--)
        {
            string name;
            int bt;

            cout << "Enter process name: ";
            cin >> name;
            cout << "Enter burst time for process: ";
            cin >>bt;

            Process p(name, bt);
            processes.push_back(p);
        }
    }

    void displayProcesses()
    {
        cout << endl;
        cout << "Process\tBT\tWT\tTAT" << endl;
        for (auto i=processes.begin(); i!=processes.end(); ++i)
        {
            cout << "   " << i->processName << "\t";
            cout << i->burstTime  << "\t";
            cout << i->waitingTime  << "\t";
            cout << i->turnAroundTime  << endl;
        }

        cout << endl;
    }

    void roundRobin()
    {
        bool isFinished = false;
        int time = 0;

        while (!isFinished)
        {
            isFinished = true;
            for (auto i=processes.begin(); i!=processes.end(); ++i)
            {
                if (i->remainingTime == 0) continue;

                if (i->remainingTime > timeQuantum)
                {
                    i->remainingTime -= timeQuantum;
                    time += timeQuantum;
                    isFinished = false;
                }
                else
                {
                    time += i->remainingTime;
                    i->remainingTime = 0;
                    i->waitingTime = (time - i->burstTime);
                    i->turnAroundTime = (i->waitingTime + i->burstTime);
                }
            }

            if (isFinished) break;
        }
    }

    void avg()
    {
        int numberOfProcesses = 0, totalWaitingTime = 0, totalTurnAroundTime = 0;

        for (auto i=processes.begin(); i!=processes.end(); ++i)
        {
            totalWaitingTime += i->waitingTime;
            totalTurnAroundTime += i->turnAroundTime;

            numberOfProcesses+=1;
        }

        float avgWaitingTime = float(totalWaitingTime) / float(numberOfProcesses);
        float avgTurnAroundTime = float(totalTurnAroundTime) / float(numberOfProcesses);

        cout << "Average Waiting Time: " << avgWaitingTime << endl;
        cout << "Average TurnAround Time: " << avgTurnAroundTime << endl;
    }
};

// ROUND ROBIN END

int main()
{
    int ch = 0;

    do
    {
        cout << "\nMenu" << endl << endl;
        cout << "1. FCFS" << endl;
        cout << "2. Non Pre-emptive SJF" << endl;
        cout << "3. Pre-emptive SJF" << endl;
        cout << "4. Pre-emptive Priority Scheduling" << endl;
        cout << "5. Non Pre-emptive Priority Scheduling" << endl;
        cout << "6. Round-Robin Scheduling" << endl;
        cout << "7. Exit" << endl<< endl;

        cout << "Enter your choice: ";
        cin >> ch;
        cout << endl;

        switch (ch)
        {
        case 1:
            fcfs();
            break;

        case 2:
        {
            int num, temp;

            cout << "Enter number of Process: ";
            cin >> num;

            cout << "...Enter the process ID...\n";
            for (int i = 0; i < num; i++)
            {
                cout << "...Process " << i + 1 << "...\n";
                cout << "Enter Process Id: ";
                cin >> mat[i][0];
                cout << "Enter Arrival Time: ";
                cin >> mat[i][1];
                cout << "Enter Burst Time: ";
                cin >> mat[i][2];
            }

            cout << "Before Arrange...\n";
            cout << "Process ID\tArrival Time\tBurst Time\n";
            for (int i = 0; i < num; i++)
            {
                cout << mat[i][0] << "\t\t" << mat[i][1] << "\t\t"
                     << mat[i][2] << "\n";
            }

            arrangeArrival(num, mat);
            completionTime(num, mat);
            cout << "Final Result...\n";
            cout << "Process ID\tArrival Time\tBurst Time\tWaiting "
                 "Time\tTurnaround Time\n";
            for (int i = 0; i < num; i++)
            {
                cout << mat[i][0] << "\t\t" << mat[i][1] << "\t\t"
                     << mat[i][2] << "\t\t" << mat[i][4] << "\t\t"
                     << mat[i][5] << "\n";
            }
        }
        break;

        case 3:
        {
            int n;
            cout << "Enter number of processes: ";
            cin >> n;

            ProcessPreSJF proc[n];
            for (int i=0; i<n; i++) {
                int pid, bt, art;
                cout << "Enter process ID: ";
                cin >> pid;
                cout << "Enter process BT: ";
                cin >> bt;
                cout << "Enter process AT: ";
                cin >> art;

                proc[i] = {pid, bt, art};
            }

            findavgTimePSJF(proc, n);
        }
        break;

        case 4: initPEPS();
            break;

        case 5:
        {
            cout << "Enter number of processes: ";
            cin >> totalprocessNPEPS;

            int arrivaltime[totalprocessNPEPS];
            int bursttime[totalprocessNPEPS];
            int priority[totalprocessNPEPS];

            for (int i=0; i<totalprocessNPEPS; i++)
            {
                cout << "Enter AT for process " << i << ": ";
                cin >> arrivaltime[i];
                cout << "Enter BT for process " << i << ": ";
                cin >> bursttime[i];
                cout << "Enter Priority for process " << i << ": ";
                cin >> priority[i];
            }

            for(int i=0; i<totalprocessNPEPS; i++)
            {
                proc[i].at=arrivaltime[i];
                proc[i].bt=bursttime[i];
                proc[i].pr=priority[i];
                proc[i].pno=i+1;
            }

            sort(proc,proc+totalprocessNPEPS,comp);

            findgc();
        }
        break;
        case 6:
        {
            RoundRobin RR(4);

            RR.inputProcesses();
            RR.displayProcesses();
            RR.roundRobin();
            RR.displayProcesses();
            RR.avg();
        }
        break;

        case 7:
            cout << "Exiting.." << endl;
            exit(0);

        default:
            cout << "Wrong choice!!!";
        }

    }
    while (ch != 7);

    return 0;
}
