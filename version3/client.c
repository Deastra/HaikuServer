#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all/shdmemory.c"
#include "all/msgqueue.c"
#include <signal.h>
#include <time.h>
#include <unistd.h>
// #include "all/haiku_reader.h"
#define MAX 255
int flag=10;
int proc;
int matr[2][2]={ {2,JAP} , {3,WEST} };

void signal_handler(int signum){
    flag--;
    printf("Signal no_%d:: ",flag);
    int q_id=access_queue();
    int cat;
    char haiku[MAX];
    for(int i=0;i<2;i++){
        if(signum==matr[i][0]){
            kill(proc,2);
            read_queue(q_id,haiku,matr[i][1]);
            printf("type:: %d\n- %s\n",matr[i][1],haiku);
            printf("------------------------------------------------------------\n");
        }
    }

    // if(signum==2){  // JAPANES
    //     printf("SIGINT || JAPANES\n");
    //     kill(proc,2);
    //     read_queue(q_id,haiku,)
    // }else if(signum==3){  // WESTERN
    //     printf("SIGQUIT || WESTERN\n");
    //     kill(proc,3);
    // }
}



int main(){
    int seg=access_segment();
    int p_id=getpid();
    
    int arr[3];
    read_values(seg,arr);
    proc=arr[0];
    // arr[1]=0; // JAPAN
    // arr[2]=1; // WEST
    // write_values(seg,arr);

    int q_id=create_queue();

    // Generate random signal
    srand(time(NULL));

    int signum=0;

    while(flag){
        sleep(1);
        signum=rand()%2+2;
        signal_handler(signum);

    }
    
    printf("END of CLIENT\n");

}

/*
// int main(){
//     int p=getpid();
//     printf("Process of client:: %d\n\n",p); 
    
//     int seg;
//     while(!(seg=access_segment())){

//     }
    
//     read_values(seg,&proc);
//     srand(time(NULL));

//     int signum=0;

//     while(flag){
//         sleep(1);
//         signum=rand()%2+2;
//         signal_handler(signum);
//     }
    
//     printf("END of CLIENT\n");
//     return 0;
// }

*/
