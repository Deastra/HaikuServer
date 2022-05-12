#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "shdmemory.c"
#define JAP 1
#define WEST 2


int matr[2][2]={ {2,JAP} , {3,WEST} };

int flag=100;
void signal_handler(int signum){

    for (int i=0;i<2;i++){
        if(signum==matr[i][0]){
            flag--;
            printf("Category is %d\n",matr[i][1]);
            return;
        }
    }
    printf("Incorrect Signal!\n");
}

int main(){
    int p=getpid();
    int seg=create_segment();
    write_values(seg,p);

    printf("Process:: %d\n\n",p); 

    if (signal(SIGQUIT, signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}


    while(flag){
        sleep(2);   
    }
    
    remove_segment(seg);
    printf("END OF MAIN\n");

    return 0;
}