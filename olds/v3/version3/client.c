#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "all/shdmemory.c"
#include "all/msgqueue.c"

void signal_handler(int signum);
int client();
int flag=20;
int proc;

int main(){
    if(client()==-1){
        puts(" ------ !!! Client Error !!! ------ \n");
    }
    return 0;
}

int client(){
  
    int p=getpid();
    printf("Process:: %d\n\n",p); 
    
    int seg=access_segment();
    read_values(seg,&proc);
    srand(time(NULL));

    if (signal(SIGQUIT, signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n"); return -1;}
    if (signal(SIGINT, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n"); return -1;}
    if (signal(SIGTSTP, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n"); return -1;}

    int signum=0;

    while(flag){
        sleep(1);
        printf("Signal %d:: ",flag);
        signum=rand()%2+2;
        signal_handler(signum);
    }
    
    printf("END of CLIENT\n");
    return 1;
}

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
