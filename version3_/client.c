#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all/shdmemory.c"
#include "all/msgqueue.c"
#include <signal.h>
#include <time.h>
#include <unistd.h>



int proc;
void signal_handler(int signum){
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
    int flag=20;
    int seg=access_segment();
    read_values(seg,&proc);
    srand(time(NULL));

    int signum=0;

    while(flag){
        sleep(1);
        printf("Signal %d:: ",flag);
        signum=rand()%2+2;
        signal_handler(signum);
        flag--;
    }
    
    printf("END of CLIENT\n");
}