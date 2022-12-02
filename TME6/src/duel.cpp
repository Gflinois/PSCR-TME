#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include "rsleep.h"
#include <string>
int pv=3;
std::string name = "undefined";
void randsleep() {
  int r = rand();
  double ratio = (double)r / (double) RAND_MAX;
  struct timespec tosleep;
  tosleep.tv_sec =0;
  // 300 millions de ns = 0.3 secondes
  tosleep.tv_nsec = 300000000 + ratio*700000000;
  struct timespec remain;
  while ( nanosleep(&tosleep, &remain) != 0) {
    tosleep = remain;
  }
}

void atkHandler(int signum){
    pv--;
    if (pv){
        std::cout<<"il reste "<<pv<<" points de vies à"<<name<<std::endl;
        return;
    }
    std::cout<<name<<" est mort."<<std::endl;
    exit(1);
}
    

void attaque (pid_t adversaire){
    std::cout<<name<<" attaque."<<std::endl;
    struct sigaction s;
    sigset_t sig_proc;
    sigemptyset(&sig_proc);
    s.sa_mask=sig_proc;
    s.sa_flags=0;
    s.sa_handler = atkHandler;

    sigaction(SIGINT,&s,NULL);
    randsleep();
    if(kill(adversaire,SIGINT)) {
        exit(0);
    }
    
    return ;
}

void defense (){

    struct sigaction s;
    sigset_t sig_proc;
    sigemptyset(&sig_proc);
    s.sa_mask=sig_proc;
    s.sa_flags=0;
    s.sa_handler = SIG_IGN;

    sigaction(SIGINT,&s,NULL);
    std::cout<<name<<" défend."<<std::endl; 
    randsleep();
    return ;
}

void combat(pid_t adversaire){
    randsleep();
    std::cout<<name<<" se bat."<<std::endl;
    
    while (true){
        defense();
        attaque(adversaire);

    }
}


int main(){
    pid_t a=fork();

    srand(getpid());
    pid_t Vador = (a) ? getpid() :getppid();
    pid_t Luke = (a) ? a : getpid();
    name = (a) ? "Vador":"Luke";
    pid_t adversaire = (a) ? Luke:Vador;
    combat(adversaire);
    wait(0);

}