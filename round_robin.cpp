#include<iostream>
#include<vector>
using namespace std;

class Process
{
public:
    int burst_time;
    int arrival_time;
    int turnAround_time;
    int waiting_time;
    int time_left;
    Process(int bt, int at);
};

Process::Process(int bt, int at) {
    burst_time = bt;
    arrival_time = at;
}


class RoundRobin
{
public:
    int nr_proc;
    int totalTurnAroundTime;
    int totalWaitTime;
    int totalProcessTime;
    int remain_processes;
    int flag = 0 ;
    vector<Process> processes;
    void inputData();
    void initRR();
    void displayTime();
    void computeRR();
};



void RoundRobin::inputData()
{
    cout<<"Enter number of processes\n";
    cin>>nr_proc;
    remain_processes = nr_proc;

    cout<<"Enter the Burst and Arrival times in order :\n";
    for(int i=0;i<nr_proc;i++){
        int bt, at;
        cout<<"Burst Time for P(" << i+1 <<"): ";
        cin>>bt;
        cout<<"Arrival Time for P(" << i+1 <<"): ";
        cin>>at;
        processes.push_back(Process(bt, at));
    }
}

void RoundRobin::initRR()
{
    totalProcessTime=0;
    totalWaitTime=0;
    totalTurnAroundTime=0;
    for(int i=0; i<nr_proc; i++)
    {
        processes[i].time_left=processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnAround_time = 0;
        totalProcessTime+=processes[i].burst_time;
    }
}

void RoundRobin::displayTime()
{

    cout<<"\n\n--------------------------------------\n";
    cout<<"Process\t|TurnAround Time|Waiting Time\n";
    cout<<"--------+---------------+-------------\n";
    for(int i=0;i<nr_proc;i++)
    {
        processes[i].turnAround_time= processes[i].waiting_time+processes[i].burst_time;
        cout<<"P("<< i+1 <<")\t|\t"<< processes[i].turnAround_time <<"\t|\t"<<  processes[i].waiting_time <<"\n";

    }
    cout<<"--------------------------------------\n\n";

    cout<<"Avg Waiting time = "<<(double)totalWaitTime/nr_proc<<endl;
    cout<<"Avg Turnaround time = "<<(double)totalTurnAroundTime/nr_proc<<endl;
    cout<<"Round Robin scheduling complete\n";
}

void RoundRobin::computeRR(){

    inputData();
    initRR();
    int currentTime;
    int i;
    int time_quantum;
    cout<<"Enter the time quantum:\n";
    cin>>time_quantum;

    cout<<"\n--------------------------------------\n";
    cout<<"Gantt Chart\n";
    cout<<"--------------------------------------\n";

    for(currentTime=0,i=0;remain_processes!=0;)
    {
        cout<<"("<<currentTime<<")|==P"<<(i+1)<<"==|";

        if(processes[i].time_left<=time_quantum && processes[i].time_left>0)
        {
            currentTime+=processes[i].time_left;
            processes[i].time_left=0;
            flag=1;
        }
        else if(processes[i].time_left>0)
        {
            processes[i].time_left-=time_quantum;
            currentTime+=time_quantum;
        }
        if(processes[i].time_left==0 && flag==1)
        {
            remain_processes--;
            processes[i].turnAround_time = currentTime-processes[i].arrival_time;
            processes[i].waiting_time = currentTime-processes[i].arrival_time-processes[i].burst_time;
            totalWaitTime+=currentTime-processes[i].arrival_time-processes[i].burst_time;
            totalTurnAroundTime+=currentTime-processes[i].arrival_time;
            flag=0;
        }
        if(i==nr_proc-1)
            i=0;
        else if(processes[i+1].arrival_time<=currentTime)
            i++;
        else
            i=0;
    }

    cout<<"("<<totalProcessTime<<")"<<endl;
    displayTime();
}

int main()
{
    RoundRobin rr;
    rr.computeRR();
}
