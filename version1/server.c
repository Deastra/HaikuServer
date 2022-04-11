#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "shdmemory.c"
#define JAP 1
#define WEST 2
int flag=10;
int matr[2][2]={ {2,JAP} , {3,WEST} };
void signal_handler(int signum){
    flag--;


    for (int i=0;i<2;i++){
        // printf("%c\n",(char)x);
        if(signum==matr[i][0]){
            printf("Category is %d\n",matr[i][1]);
            return;
        }
    }
    printf("Incorrect Signal!\n");
    // if(signum==2){
    //     printf("Category:: japanese\n");
    // }else if(signum==3){
    //     printf("Category:: western\n");
    // }else{
    //     printf("Not categorized\n");
    // }
}

int main(){
    int p=getpid();
    int seg=create_segment();
    write_values(seg,p);

    if (signal(SIGQUIT, signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}


    while(flag){
        sleep(2);
        printf("waiting for signal...\nProcess:: %d\n",p);    
    }
    
    remove_segment(seg);
    printf("END OF MAIN\n");

    return 0;
}