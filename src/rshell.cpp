#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <fstream>
using namespace std;
#include <signal.h>

int systems(const char *cmd)
{
    int stat;
    pid_t pid;
    struct sigaction sa, savintr, savequit;
    sigset_t saveblock;
    if (cmd == NULL)
    	perror("cmd is null");
        return(1);
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigemptyset(&savintr.sa_mask);
    sigemptyset(&savequit.sa_mask);
    sigaction(SIGINT, &sa, &savintr);
    sigaction(SIGQUIT, &sa, &savequit);
    sigaddset(&sa.sa_mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sa.sa_mask, &saveblock);
    if ((pid = fork()) == 0) {
        sigaction(SIGINT, &savintr, (struct sigaction *)0);
        sigaction(SIGQUIT, &savequit, (struct sigaction *)0);
        sigprocmask(SIG_SETMASK, &saveblock, (sigset_t *)0);
        execl("/bin/sh", "sh", "-c", cmd, (char *)0);
        _exit(127);
    }
    if (pid == -1) {
    	perror("err comes from fork");
        stat = -1; /* errno comes from fork() */
    } else {
        while (waitpid(pid, &stat, 0) == -1) {
            if (errno != EINTR){
                stat = -1;
                break;
            }
        }
    }
    sigaction(SIGINT, &savintr, (struct sigaction *)0);
    sigaction(SIGQUIT, &savequit, (struct sigaction *)0);
    sigprocmask(SIG_SETMASK, &saveblock, (sigset_t *)0);
    return(stat);
}

int main() {
   cout<<"write the file you want to run. "<<endl;
   string filename;
   cin>>filename;
   //string filename = "1235.sh";
   //string filename = "/Users/tianrunsun/Desktop/Rshell/tests/exit.sh";
   ifstream infile(filename.c_str());
   string t;
   while(getline(infile,t))
   {

	int STATUS = -1;
	char command[1024];
	strcpy(command, t.c_str());
	//char command[] = "ls;ls;ls";


	const char *d = "#";
	char * arr;
	vector<char*> temp;
	arr = strtok(command, d);

	while (arr) {
		//printf("%s\n", arr);
		temp.push_back(arr);
		arr = strtok(NULL, d);
	}
	char * ins = temp[0];
	const char *d1 = ";";
	char * arr1;
	vector<char*> temp1;
	arr1 = strtok(ins, d1);
	while (arr1) {
		//printf("%s\n", arr1);
		temp1.push_back(arr1);
		arr1 = strtok(NULL, d1);

	}
	for (int i = 0; i < temp1.size(); i++) {
		const char *d2 = "||";
		char * arr2;
		vector<char*> temp2;
		arr2 = strtok(temp1[i], d2);
		while (arr2) {
			//printf("%s\n", arr2);
			temp2.push_back(arr2);
			arr2 = strtok(NULL, d2);
		}
		for (int j = 0; j < temp2.size(); j++) {
			const char * d3 = "&&";
			char * arr3;
			//vector<char*> temp3;
			arr3 = strtok(temp2[j], d3);
			while (arr3){
				printf("%s\n$", arr3);
				if (strcmp(arr3,"exit")==0) {
					//cout<<"exit";
					return 0;
					
				}
				
				int status = systems(arr3);
				
				if(status!=0){
					STATUS = -1;
					break;
				}
				else
				{
					STATUS = 0;
				}

				arr3 = strtok(NULL, d3);
			}
			if(STATUS==0){
				break;
			}
		}
	}
}
	//getchar();
	return 0;
}
