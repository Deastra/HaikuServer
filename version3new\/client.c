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
#define JAP 1
#define WEST 2
int flag=10;
int proc;
int matr[2][2]={ {2,JAP} , {3,WEST} };
int arr[3];
void signal_handler(int signum){
    flag--;
    int seg=access_segment();


    printf("Signal no_%d || signal:: %d -- ",flag,signum);
    int q_id=access_queue();
    int cat;
    char haiku[MAX];
    for(int i=0;i<2;i++){
        if(signum==matr[i][0]){
            cat=matr[i][1];
            kill(proc,signum);
            printf("run %d\n",flag);
            read_values(seg,arr);
            while(arr[cat]==0){
                read_values(seg,arr);
            }
            puts("read values");
            read_queue(q_id,haiku,matr[i][1]);
            puts("read queue");

            printf("arr %d\n",arr[cat]);
            arr[cat]--;
            write_values(seg,arr);
            puts("wrote values");
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
    printf("Process:: %d\n\n",p_id); 
    
    read_values(seg,arr);
    proc=arr[0];
    // arr[1]=0; // JAPAN
    // arr[2]=1; // WEST
    // write_values(seg,arr);

    int q_id=create_queue();

    // Generate random signal
    srand(time(NULL));

    int signum=0;
    int carr[2];
    carr[0]=0;
    carr[1]=0;
    while(flag){
        sleep(1);
        signum=rand()%2+2;
        signal_handler(signum);
        carr[signum-2]++;

    }
    // arr[1]=0;
    // arr[2]=0;
    // write_values(seg,arr);
    printf("END of CLIENT\n");

    printf("Number of haikus read:: %d %d\n",carr[0],carr[1]);

    remove_queue(q_id);

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
