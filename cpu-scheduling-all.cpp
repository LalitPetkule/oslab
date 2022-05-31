#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void FCFS(int num, int burst_time[])
{
    int waiting_time[num];
    waiting_time[0]=0;
    for(int i=1;i<num;i++)
    {
        waiting_time[i]=waiting_time[i-1]+burst_time[i-1];
    }
    int turn_around_time[num];
    for(int i=0;i<num;i++)
    {
        turn_around_time[i]=waiting_time[i]+burst_time[i];
    }
    cout << "Processes  "<< " Burst time  "
         << " Waiting time  " << " Turn around time\n";
    for (int  i=0; i<num; i++)
    {
        cout << "   " << i+1 << "\t\t" << burst_time[i] <<"\t    "
            << waiting_time[i] <<"\t\t  " << turn_around_time[i] <<endl;
    }
    int avg_waiting_time=(accumulate(waiting_time, waiting_time + num, 0)/num);
    int avg_turn_around_time=(accumulate(turn_around_time, turn_around_time + num, 0)/num);
    cout<<"Average waiting time : "<<avg_waiting_time;
    cout<<"\nAverage turn around time : "<<avg_turn_around_time;

}
void SJF(int num, int burst_time[], int index[])
{
    int wt[20], tat[20], avwt=0, avtat=0, i, j;
    for(i=0;i<num;i++){
        for(j=i;j<num;j++){
            if(burst_time[j]<burst_time[i]){
                swap(burst_time[i], burst_time[j]);
                swap(index[i], index[j]);
            }
        }
    }

    wt[0]=0;
    cout<<endl<<"Process\t\tBurst Time\tWaiting Time\tTurnaround Time"<<endl;
    for(i=0;i<num;i++){
        wt[i+1]= wt[i]+burst_time[i];
        tat[i]= wt[i]+burst_time[i];
        avwt=avwt+wt[i];
        avtat=avtat+tat[i];
        cout<<"P "<<index[i]+1<<" \t\t"<<burst_time[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<endl;
    }

    cout<<endl<<"Average Waiting Time: "<<avwt/i<<endl;
    cout<<"Average Turnaround Time: "<<avtat/num<<endl;
}
void SJF_non(int num, int burst_time[],int arrival_time[], int index[])
{
    int temp,tt=0,min,d,i,j;
    float atat=0,awt=0,stat=0,swt=0;
    int e[num],tat[num],wt[num];
    for(i=0;i<num;i++)
      {
         for(j=i+1;j<num;j++)
          {
                if(burst_time[i]>burst_time[j])
                {
                      swap(burst_time[i], burst_time[j]);
                      swap(index[i], index[j]);
                      swap(arrival_time[i],arrival_time[j]);
                }
          }
      }
      min=arrival_time[0];
      for(i=0;i<num;i++)
      {
            if(min>arrival_time[i])
            {
                  min=arrival_time[i];
                  d=i;
            }
      }
      tt=min;
      e[d]=tt+burst_time[d];
      tt=e[d];

      for(i=0;i<num;i++)
      {
            if(arrival_time[i]!=min)
            {
                  e[i]=burst_time[i]+tt;
                  tt=e[i];
            }
      }
      for(i=0;i<num;i++)
      {

            tat[i]=e[i]-arrival_time[i];
            stat=stat+tat[i];
            wt[i]=tat[i]-burst_time[i];
            swt=swt+wt[i];
      }
      atat=stat/num;
      awt=swt/num;
      cout<<"Process  Arrival-time(s)  Burst-time(s)  Waiting-time(s)  Turnaround-time(s)\n";

    for(i=0;i<num;i++)
    {
    cout<<"P"<<index[i]+1<<" \t\t"<<arrival_time[i]<<" \t\t"<<burst_time[i]<<" \t\t"<<wt[i]<<" \t\t"<<tat[i]<<endl;
    }

    cout<<"Average Waiting Time : "<<awt<<"\nAverage Turnaround Time : "<<atat;
}

void priority(int n, int p[], int bt[], int pr[])
{
    int i,j,pos,temp,avg_tat,avg_wt,total=0;
    int wt[n],tat[n];
    for (i=0;i<n;i++) {
		pos=i;
		for (j=i+1;j<n;j++) {
			if(pr[j]<pr[pos])
                pos=j;
		}
		temp=pr[i];
		pr[i]=pr[pos];
		pr[pos]=temp;
		temp=bt[i];
		bt[i]=bt[pos];
		bt[pos]=temp;
		temp=p[i];
		p[i]=p[pos];
		p[pos]=temp;
	}
	wt[0]=0;
	for (i=1;i<n;i++) {
		wt[i]=0;
		for (j=0;j<i;j++)
            wt[i]+=bt[j];
		total+=wt[i];
	}
	avg_wt=total/n;
	total=0;
	cout<<"Process  Burst-time(s)  Waiting-time(s)  Turnaround-time(s)\n";
	for (i=0;i<n;i++) {
		tat[i]=bt[i]+wt[i];
		total+=tat[i];
		cout<<"P "<<p[i]<<" \t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<endl;
	}
	avg_tat=total/n;
	cout<<"\nAverage Waiting Time="<<avg_wt;
	cout<<"\nAverage Turnaround Time="<<avg_tat;
}
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum)
{
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] = bt[i];

    int t = 0;
    while (1)
    {
        bool done = true;
        for (int i = 0 ; i < n; i++)
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
                    t = t + rem_bt[i];
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
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
void round_robin(int n, int processes[], int bt[], int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);
    cout << "Processes "<< " Burst time "<< " Waiting time " << " Turn around time\n";

    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i+1 << "\t\t" << bt[i] <<"\t "<< wt[i] <<"\t\t " << tat[i] <<endl;
    }

    cout << "Average waiting time = "<< (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "<< (float)total_tat / (float)n;
}

int main()
{
    int ch=0,a=1;
    while(a)
    {
        cout<<"\nCPU Scheduling Algorithms.\n";
        cout<<"\n1.First Come First Serve\n2.Shortest Job First (Non-Preemptive)\n3.Shortest Job First (Preemptive)\n4.Priority Based\n5.Round Robin";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        int num;
        cout<<"Enter the number of processes : ";
        cin>>num;
        int burst_time[num];
        int index[num];
        int arrival_time[num];
        cout<<"Enter the burst time for each process : ";
        for(int i=0;i<num;i++)
        {
            cout<<"\nP "<<i+1<<" : ";
            cin>>burst_time[i];
            index[i]=i;
        }
        switch(ch)
        {
            case 1:"\nFirst Come First Serve";
                   FCFS(num, burst_time);
                   break;
            case 2:"\nShortest Job First (Non-Preemptive)";
                   SJF(num, burst_time, index);
                   break;
            case 3:
                {
                    cout<<"\nShortest Job First (Preemptive)";
                    cout<<"\nEnter the arrival time for each process : ";
                    for(int i=0;i<num;i++)
                    {
                        cout<<"\nP "<<i+1<<" : ";
                        cin>>arrival_time[i];
                    }
                    SJF_non(num, burst_time, arrival_time, index);
                }
                   break;
            case 4:
                {
                    cout<<"\nPriority Based";
                    cout<<"\nEnter the Priority for each process : ";
                    int pr[num];
                    for(int i=0;i<num;i++)
                    {
                        cout<<"\nPriority "<<i+1<<" : ";
                        cin>>pr[i];
                    }
                    priority(num, index, burst_time, pr);
                }
                   break;
            case 5:
                {
                   "\nRound Robin";
                   int quantum=0;
                   cout<<"\nEnter the time slice : ";
                   cin>>quantum;
                   round_robin(num,index,burst_time,quantum);
                }
                   break;
            default:"\nWrong choice.";
        }
        cout<<"\nDo you want to continue(1/0) : ";
        cin>>a;
    }
    return 0;
}
