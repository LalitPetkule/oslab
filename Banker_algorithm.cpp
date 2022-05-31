// Banker's Algorithm
#include <iostream>
using namespace std;

int main()
{
int n, m, i, j, k;
n = 5; // Number of processes
m = 3; // Number of resources
int alloc[5][3];
int max[5][3];


cout<<"\n Enter allocation matrix:";
for(int i=0;i<5;i++)
{
	for(int j=0;j<3;j++)
	{
		cout<<"\nalloc["<<i<<"]["<<j<<"]=  ";
		cin>>alloc[i][j];
	}
}

cout<<"\n Enter max matrix:";
for(int i=0;i<5;i++)
{
	for(int j=0;j<3;j++)
	{
		cout<<"\nmax["<<i<<"]["<<j<<"]=  ";
		cin>>max[i][j];
	}
}

int avail[3] = { 3, 3, 2 }; // Available Resources

int f[n], ans[n], ind = 0;
for (k = 0; k < n; k++) {
	f[k] = 0;
}
int need[n][m];
for (i = 0; i < n; i++) {
	for (j = 0; j < m; j++)
	need[i][j] = max[i][j] - alloc[i][j];
}
int y = 0;
for (k = 0; k < 5; k++) {
	for (i = 0; i < n; i++) {
	if (f[i] == 0) {

		int flag = 0;
		for (j = 0; j < m; j++) {
		if (need[i][j] > avail[j]){
			flag = 1;
			break;
		}
		}

		if (flag == 0) {
		ans[ind++] = i;
		for (y = 0; y < m; y++)
			avail[y] += alloc[i][y];
		f[i] = 1;
		}
	}
	}
}

cout << "Following is the SAFE Sequence" << endl;
for (i = 0; i < n - 1; i++)
	cout << " P" << ans[i] << " ->";
cout << " P" << ans[n - 1] <<endl;

	return (0);
}



