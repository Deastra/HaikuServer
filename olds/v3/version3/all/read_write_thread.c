#ifndef RWT
#define RWT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shdmemory.c"
#include "msgqueue.c"
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define JAP 1
#define WEST 2
#define MAX 255

int matr[2][2]={ {2,JAP} , {3,WEST} };
int flag=1;
int n_haiku[2];

void write_haiku(int category){ 
    
    int q=access_queue();
    
    char fileName[MAX];
    int count=0;
    
    if (category==JAP){
        strcpy(fileName, "japanese.txt");
        
    }else{
        strcpy(fileName, "western.txt");
    }

    FILE* file = fopen(fileName, "r"); 
    
    char line[MAX];
    int length=0;
    puts("cccccccc\n");
    fgets(line, sizeof(line), file);
    puts("aaaaaaaaaa\n");
    printf("line:: %s\n",line);
    while(fgets(line, sizeof(line), file)!=NULL) {    
        
        length = strlen(line);
        line[length - 1] = '\0';
        
        write_queue(q,line,category);
        count++;
        printf("writing haiku of cat %d :: %d)- %s\n",category,count,line);
        n_haiku[category-1]++;
    }

    fclose(file);
    printf("Haikus of type %d are written!\n",category);

}

void* writer_thread(void* category){
    int *cat=(int*)category;
    
    
    if(n_haiku[(*cat)-1]==0){
        puts("***********************************\n");
        puts("EMPTY QUEUE, writing....\n");
        printf("category writer:: %d\n",*cat);
        puts("***********************************\n");
        write_haiku(*cat);
        puts("***********************************\n");
    }


    pthread_exit(NULL);
}

void* reader_thread(void* category){
    puts("here");
    int *cat=(int*)category;
    int q_id=access_queue();
    
    char haiku[MAX];
    
    read_queue(q_id,haiku,*cat);
    puts("-----------------------------------------\n");
    printf("%d)cat %d - %s\n",flag,*cat,haiku);
    puts("-----------------------------------------\n");
    n_haiku[(*cat)-1]--;
    pthread_exit(NULL);
}

void add_thread(int category){
    pthread_t tid [2] ;

    if (pthread_create (&tid [0], NULL, &writer_thread, (void*) &(category)) == -1){
        // error ("pthread_create") ;
        
        puts("COULDNT CREATE");
        flag=0;
        return;
    }
    
    if (pthread_create (&tid [1], NULL, &reader_thread, (void*) &(category)) == -1){
        // error ("pthread_create") ;
        
        puts("COULDNT CREATE");
        flag=0;
        return;
    }  
    
    ///////////////// JOIN
    
    for(int i=0;i<2;i++){
        if (pthread_join (tid [i], NULL) == -1){
            // error ("pthread_join") ;
            puts("COULDNT JOIN");
            flag=0;
            return;
        }   
        puts("there2");
    }
    return;
 
}


#endif