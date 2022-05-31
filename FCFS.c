#include<stdio.h>
#include<stdlib.h>


typedef struct process {
	char name[5];
	int bt;
	int at;
	int prt;
	int wt, ta;
	int flag;
}
processes;

void Sort_By_ArrivalTime(processes proc[], int n) {
	processes t;
	int i, j;
	for (i = 1; i < n; i++)
		for (j = 0; j < n - i; j++) {
			if (proc[j].at > proc[j + 1].at) {
				t = proc[j];
				proc[j] = proc[j + 1];
				proc[j + 1] = t;
			}
		}
}

int get_Processes(processes P[]) {
	int i, n;
	printf("\n Enter total no. of processes : ");
	scanf("%d", & n);
	for (i = 0; i < n; i++) {
		printf("\n PROCESS [%d]", i + 1);
		printf(" Enter process name : ");
		scanf("%s", & P[i].name);
		printf(" Enter burst time : ");
		scanf("%d", & P[i].bt);
		printf(" Enter arrival time : ");
		scanf("%d", & P[i].at);
	}
	printf("\n PROC.\tB.T.\tA.T.");
	for (i = 0; i < n; i++)
		printf("\n %s\t%d\t%d", P[i].name, P[i].bt, P[i].at);
	return n;
}

// FCFS Algorithm
void FCFS(processes P[], int n) {
	processes proc[10];
	int sumw = 0, sumt = 0;
	int x = 0;
	float avgwt = 0.0, avgta = 0.0;
	int i, j;
	for (i = 0; i < n; i++)
		proc[i] = P[i];


	Sort_By_ArrivalTime(proc, n);


	printf("\n\n PROC.\tB.T.\tA.T.");
	for (i = 0; i < n; i++)
		printf("\n %s\t%d\t%d", proc[i].name, proc[i].bt, proc[i].at);


	sumw = proc[0].wt = 0;
	sumt = proc[0].ta = proc[0].bt - proc[0].at;


	for (i = 1; i < n; i++) {
		int temp = (proc[i - 1].bt + proc[i - 1].at + proc[i - 1].wt) - proc[i].at;
		proc[i].wt = temp < 0 ? 0:temp;
		proc[i].ta = proc[i].wt + proc[i].bt;
		sumw += proc[i].wt;
		sumt += proc[i].ta;
	}
	avgwt = (float) sumw / n;
	avgta = (float) sumt / n;
	printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
	for (i = 0; i < n; i++)
		printf("\n %s\t%d\t%d\t%d\t%d", proc[i].name, proc[i].bt, proc[i].at, proc[i].wt, proc[i].ta);

	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", avgwt, avgta);
}

int main() {

	processes P[10];
	int ch, n;
	do {
		printf("\n\n SIMULATION OF CPU SCHEDULING ALGORITHMS\n");
		printf("\n Options:");
		printf("\n 0. Enter process data.");
		printf("\n 1. FCFS");
		printf("\n 2. Exit\n Select : ");
		scanf("%d", & ch);
		switch (ch) {
			case 0:
				n = get_Processes(P);
				break;
			case 1:
				FCFS(P, n);
				break;

			case 2:
				exit(0);
		}
	} while (ch != 2);
	return 0;
}
