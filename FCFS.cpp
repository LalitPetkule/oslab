#include<iostream>
 
using namespace std;
 
int main()
{
    int n,bt[20],wt[20],tat[20],avwt=0,avtat=0,i,j;
    cout<<"Enter total number of processes:";
    cin>>n;
 
    cout<<"\nEnter Process Burst Time\n";
    for(i=0;i<n;i++)
    {
        cout<<"P["<<i+1<<"]:";
        cin>>bt[i];
    }
 
    wt[0]=0;    //waiting time for first process is 0
 
    //calculating waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }
 
    cout<<"\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";
 
    //calculating turnaround time
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avwt+=wt[i];
        avtat+=tat[i];
        cout<<"\nP["<<i+1<<"]"<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i];
    }
 
    avwt/=i;
    avtat/=i;
    cout<<"\n\nAverage Waiting Time:"<<avwt;
    cout<<"\nAverage Turnaround Time:"<<avtat;
 
    return 0;
}

//#include<bits/stdc++.h>
//
//using namespace std;
//
//// FCFS
//int main()
//{
//    int num;
//    cout << "Enter number of processes: ";
//    cin >> num;
//
//    string  process[num];
//    int bt[num], wt[num], tat[num], sumWT = 0, sumTAT = 0;
//    wt[0] = 0;
//    tat[0] = bt[0];
//
//    for (int i=0; i<num; i++)
//    {
//        cout << "Enter BT for process P" << i << ": ";
//        cin >> bt[i];
//
//        if (i > 0)
//        {
//            wt[i] = bt[i-1] + wt[i-1];
//        }
//
//        tat[i] = bt[i] + wt[i];
//
//        sumWT += wt[i];
//        sumTAT += tat[i];
//    }
//
//    cout << endl << "Processes are: " << endl << endl;
//
//    cout << "Process \t BT" << endl;
//    for (int i=0; i<num; i++)
//    {
//        cout << "   P" << i << "   \t" << bt[i] << "ms" << endl;
//    }
//
//    cout << endl << "WT and TAT Calculated: " << endl << endl;
//
//    cout << "Process \t BT \t WT \t TAT" << endl;
//    for (int i=0; i<num; i++)
//    {
//        cout << "   P" << i << "   \t";
//        cout << bt[i] << "ms" << "\t";
//        cout << wt[i] << "ms" << "\t";
//        cout << tat[i] << "ms" << endl;
//    }
//
//    cout << endl;
//    cout << "Average WT: " << sumWT/num << "ms" << endl;
//    cout << "Average TAT: " << sumTAT/num << "ms" << endl;
//    return 0;
//
//}
