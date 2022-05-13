#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all/shdmemory.c"
#include "all/msgqueue.c"
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#define JAP 1
#define WEST 2


int gcount=500;
int x[2];

int flag=10;
int matr[2][2]={ {2,JAP} , {3,WEST} };
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

void* haiku_write_thread(void* category){
    int* cat=(int*) category;
    // write_haiku(*cat);
    int count=50;
    // int y=x[*cat];
    
    while(1){
        printf("In writer:: %d\n",count);
        // printf("%d \n")
        // x[*cat]++;
        sleep(1);
        gcount--;
        count--;
    }
    pthread_exit(NULL);
    // return NULL;

}

void* haiku_read_thread(void* category){
    int* cat=(int*) category;
    // write_haiku(*cat);
    int count=50;
    // while(count){
    //     sleep(1);
    //     printf("%d \n",*cat);
    //     count--;
    // }
    
    while(1){
        printf("In reader:: %d\n",count);
        // x[*cat]--;
        // printf("%d \n")
        gcount--;
        sleep(1);
        count--;
    }
    pthread_exit(NULL);
    // return NULL;

}


int main(){

    pthread_t tid [4] ; 
    int cat1=1,cat2=2;
    int cat_arr[2]={1,2};

    // int p=getpid();
    // int seg=create_segment();
    // write_values(seg,p);

    // printf("Process:: %d\n\n",p); 

    // if (signal(SIGQUIT, signal_handler) == SIG_ERR){
    //     perror("can't catch SIGQUIT\n");}
    // if (signal(SIGINT, signal_handler) == SIG_ERR){
    //     perror("can't catch SIGINT\n");}
    x[0]=0;
    x[1]=0;
    int arr[10]={0,1,2,3,4,5,6,7,8,9};
    // for(int i=0;i<2;i++){
        // printf("thread: %d ",i);
        if (pthread_create (&tid [0], NULL, &haiku_write_thread, (void*) &(arr[0])) == -1){
            // error ("pthread_create") ;
            puts("COULDNT CREATE");
            return -1;
        }
        if (pthread_create (&tid [1], NULL, &haiku_read_thread, (void*) &(arr[0])) == -1){
            // error ("pthread_create") ;
            puts("COULDNT CREATE");
            return -1;
        }
        if (pthread_create (&tid [2], NULL, &haiku_write_thread, (void*) &(arr[0])) == -1){
            // error ("pthread_create") ;
            puts("COULDNT CREATE");
            return -1;
        }

        if (pthread_create (&tid [3], NULL, &haiku_read_thread, (void*) &(arr[0])) == -1){
            // error ("pthread_create") ;
            puts("COULDNT CREATE");
            return -1;
        }
    // }

    ///////////////// JOIN
    for(int i=0;i<4;i++){
        if (pthread_join (tid [i], NULL) == -1){
            // error ("pthread_join") ;
            puts("COULDNT JOIN");
            return -1;
        }   
    }



    // while(flag){
    //     sleep(2);   
    // }
    
    // remove_segment(seg);


    puts("end of server");
    return 0;
}