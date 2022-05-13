#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "shdmemory.c"

int flag=10;
int proc;
void signal_handler(int signum){
    flag--;
    printf("Signal %d:: ",flag);
    if(signum==2){
        printf("SIGINT\n");
        kill(proc,2);
    }else if(signum==3){
        printf("SIGQUIT\n");
        kill(proc,3);
    }
}

int main(){
    
    int p=getpid();
    printf("Process:: %d\n\n",p); 

    int seg=access_segment();
    read_values(seg,&proc);
    srand(time(NULL));

    int signum=0;

    while(flag){
        sleep(1);
        signum=rand()%2+2;
        signal_handler(signum);
    }
    
    printf("END of CLIENT\n");
}