#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all/shdmemory.c"
#include "all/msgqueue.c"
#include <signal.h>
#include <time.h>
#include <unistd.h>


int flag=20;
int proc;

void signal_handler(int signum){
    flag--;
    if(signum==SIGTSTP){
        puts("EXIT");
        exit(1);
    }else{
        if(signum==2){
            printf("SIGINT\n");
            kill(proc,2);
        }else if(signum==3){
            printf("SIGQUIT\n");
            kill(proc,3);
        }
    }
}

int main(){
    
    int p=getpid();
    printf("Process:: %d\n\n",p); 
    
    int seg=access_segment();
    read_values(seg,&proc);
    srand(time(NULL));

    if (signal(SIGQUIT, signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}
    if (signal(SIGTSTP, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}


    int signum=0;

    while(flag){
        sleep(1);
        printf("Signal %d:: ",flag);
        signum=rand()%2+2;
        signal_handler(signum);
    }
    
    printf("END of CLIENT\n");
}