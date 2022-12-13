#include <cstring>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;
int main(){
    int fd[2];
    pipe(fd);
    cout<<fd[0]<<endl;
    cout<<fd[1]<<endl;
    pid_t pp=getpid();
    pid_t f1;
    pid_t f2;
    
    if ((f1=fork())==0){
        f1 = getpid();
		dup2(fd[0],0);
        
        close (fd[0]); 
        close (fd[1]);
        execl("/bin/cat","cat","bloupeee.txt",NULL);

    }

    else if ((f2=fork())==0){
        f2 = getpid();
		dup2(fd[1],1);
        close (fd[0]); 
        close (fd[1]);
        
    }
    wait(nullptr);
    wait(nullptr);
    return 0;
}