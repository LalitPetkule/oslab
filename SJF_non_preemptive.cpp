#include<iostream>
#include<stdlib.h>
using namespace std;

void sorting1(int A[10],int n)
{
    for (int i=0;i<n;i++)
    {
        for (int j=i;j<n;j++)
        {
            if(A[i]>A[j])
            {
                swap(A[i],A[j]);
                // temp=A[j];
            }
        }
    }
}
void input()//without arrival time
{
    int n=0, at[10],bt[10],wt[10],sumw=0,sumt=0,ta[10];
    cout<<"Enter the number of processes:";
    cin>>n;
    //burst time
    cout<<"Enter the burst time for "<<n<<" processes"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>bt[i];
    }
    //sorting burst time
 
    cout<<endl;
    cout<<"process \t Burst time"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<" \t \t\t"<<bt[i]<<endl;
    }
    sorting1(bt,n);
    cout<<"After sorting\n";
    cout<<"process \t Burst time"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<" \t\t\t"<<bt[i]<<endl;
    }

    //turn around time ta=summation of above times
    ta[0]=bt[0];
    sumt+=ta[0];
    for(int i=1;i<n;i++)
    {
        ta[i]=ta[i-1]+bt[i];
        sumt=sumt+ta[i];
    }

    //wait time
    for(int i=0;i<n;i++)
    {
        wt[i]=ta[i]-bt[i];
        sumw=sumw+wt[i];
    }

    cout<<"\n\nprocess \t Burst time \t wait time \t Turn around time"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<i+1<<" \t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t\t"<<ta[i]<<endl;
    }
    cout<<"\nAverage Waiting time: "<<sumw/n<<endl;
    cout<<"\nAverage Turnaround time: "<<sumt/n<<endl;
}


int main()
{

input();

return 0;
}
