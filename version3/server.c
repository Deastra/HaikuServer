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
#define MAX 255
\
int flag=0;
int matr[2][2]={ {2,JAP} , {3,WEST} };
int n_haiku[2];



void write_haiku(int category){ 
    
    int q=access_queue();
    
    char fileName[MAX];
    int count=0;
    
    if (category==JAP){
        strcpy(fileName, "all/japanese.txt");
        // count=JAP;
    }else{
        strcpy(fileName, "all/western.txt");
        // count=WEST;
    }

    FILE* file = fopen(fileName, "r"); 
    
    char line[255];
    int length=0;
    
    while(fgets(line, sizeof(line), file)!=NULL) {    
        length = strlen(line);
        line[length - 1] = '\0';
        write_queue(q,line,category);
        count++;
        printf("writing haiku of cat %d :: %d)- %s\n",category,count,line);
        n_haiku[category-1]++;
        
    }

    fclose(file);
    // printf("Haikus of type %d are written!\n",category);
    // 
    // return NULL;
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

    int *cat=(int*)category;
    int q_id=access_queue();
    // printf("category reader:: %d\n",*cat);
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
        return;
    }

    if (pthread_create (&tid [1], NULL, &reader_thread, (void*) &(category)) == -1){
        // error ("pthread_create") ;
        puts("COULDNT CREATE");
        return;
    }  
    
    ///////////////// JOIN
    
    for(int i=0;i<2;i++){
        if (pthread_join (tid [i], NULL) == -1){
            // error ("pthread_join") ;
            puts("COULDNT JOIN");
            return;
        }   
    }


    return;
 
}

void main_signal_handler(int signum){
    flag++;
    int cat;
    if(signum==20){
        exit(1);
    }else{
        printf("signal:: %d\n",signum);
        for(int i=0;i<2;i++){
            if(signum==matr[i][0]){
                cat=matr[i][1];
                add_thread(cat);
            }
        }
        return;
    }
}



int main(){


    int p=getpid();
    // int seg=create_segment();
    // write_values(seg,p);
    
    int q_id=create_queue();
    n_haiku[0]=0;
    n_haiku[1]=0;
    printf("Process:: %d\n\n",p); 

    if (signal(SIGQUIT, main_signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, main_signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}
    if (signal(SIGTSTP, main_signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}

    while(flag<20){
        sleep(1);
        printf("waiting %d...\n",flag);
        // flag--;
    }
    // remove_segment(seg);

    remove_queue(q_id);
    puts("end of server");
    return 0;
}