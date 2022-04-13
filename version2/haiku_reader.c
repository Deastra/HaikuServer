#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "msgqueue.c"


void read_haiku(int category){
    
    int q=access_queue();
    puts("IN FUNCTION READER\n");
    char arr[MAX];
    
    for(int i=0;i<3;i++){
        read_queue(q,arr,category);    
        printf("%s \n",arr);
    }

    printf("HAIKUS ARE READ!\n");
    printf("################\n");
    
}

void* haiku_thread(void* category){
    int *cat=(int*)category;
    read_haiku(*cat);
    pthread_exit(NULL);
}


int main (int argc, char *argv []){
    
    pthread_t tid [3] ; 
    
    int q=create_queue();
    
    int cat1=1;
    int cat2=2;


    /////////////// CREATE
    if (pthread_create (&tid [0], NULL, &haiku_thread, (void*) &cat1) == -1){
        // error ("pthread_create") ;
        puts("COULDNT CREATE");
    }
    if (pthread_create (&tid [1], NULL, &haiku_thread, (void*) &cat2) == -1){
        // error ("pthread_create") ;
        puts("COULDNT CREATE");
    }
    if (pthread_create (&tid [2], NULL, &haiku_thread, (void*) &cat2) == -1){
        // error ("pthread_create") ;
        puts("COULDNT CREATE");
    }

    ///////////////// JOIN
    if (pthread_join (tid [0], NULL) == -1){
        // error ("pthread_join") ;
        puts("COULDNT JOIN");
    }    
    if (pthread_join (tid [1], NULL) == -1){
        // error ("pthread_join") ;
        puts("COULDNT JOIN");
    }
    if (pthread_join (tid [2], NULL) == -1){
        // error ("pthread_join") ;
        puts("COULDNT JOIN");
    }
    int d;
    scanf("%d",&d);
    remove_queue(q);
    printf("READER FINISHED!\n");
    
}