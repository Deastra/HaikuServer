#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "shdmemory.c"

int flag=1;
int proc;
void signal_handler(int signum){
    flag=0;
    if(signum==2){
        printf("SIGINT\n");
        kill(proc,2);
    }else if(signum==3){
        printf("SIGQUIT\n");
        kill(proc,3);
    }
    // }else{
    //     printf("ELSE and KILL\n");
    //     kill(proc,9);
    // }
}

int main(){

    int seg=access_segment();
    read_values(seg,&proc);

    if (signal(SIGQUIT, signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}


    while(flag){
        sleep(2);
        printf("waiting signal for process %d ...\n",proc);
    }
    printf("END of CLIENT\n");
}