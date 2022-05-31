// C++ Code to demonstrate getppid()
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <stdio.h>
#include <sys/wait.h>
using namespace std;
int main()
{
	int pid;
	pid = fork();
	if (pid == 0)
	{
			write(1,"In child process\n",strlen("In child process\n")); 
		cout << "\nChild Process with parent id : "
			<< getppid() << endl;
			
			execlp("/bin/ls","ls",NULL);
	}
        else 
        {
            wait(NULL); //parent waiting for the child to complete
	    write(1,"In Parent Process\n",strlen("In Parent Process"));
            cout << "\nParent Process id : "
			<< getpid() << endl;
        }
	return 0;
}
