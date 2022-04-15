#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "msgqueue.c"
#include <time.h>
#define JAP 6
#define WEST 9


void write_haiku(int category){
    
    int q=access_queue();
    char fileName[MAX];
    int count;
    
    if (category==1){
        strcpy(fileName, "japanese.txt");
        count=JAP;
    }else{
        strcpy(fileName, "western.txt");
        count=WEST;
    }

    FILE* file = fopen(fileName, "r"); 
    
    char line[255];
    int length=0,j=0;

    while(fgets(line, sizeof(line), file)!=NULL) {
        
        length = strlen(line);
        line[length - 1] = '\0';
        write_queue(q,line,category);
        j++;
    }

    fclose(file);
    // return NULL;
}

void* haiku_thread(void* category){
    int* cat=(int*) category;
    write_haiku(*cat);
    pthread_exit(NULL);
    // return NULL;
}

int generateRandomNumber(int count){
    int number;
	number = (rand() % (count + 1));
    return number;
}



int main (int argc, char *argv []){
    
    pthread_t tid [3] ; 
    int cat1=1;
    int cat2=2;

    ///////////////// CREATE
    if (pthread_create (&tid [0], NULL, &haiku_thread, (void*) &cat1) == -1){
        // error ("pthread_create") ;
        puts("COULDNT CREATE");
    }
    if (pthread_create (&tid [1], NULL, &haiku_thread, (void*) &cat2) == -1){
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


}