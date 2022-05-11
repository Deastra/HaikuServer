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


// array confusing of processes id
// *i problem in thread function

int flag=20;
int matr[2][2]={ {2,JAP} , {3,WEST} };
int thread_arr[4];
int n_haiku[2];


void write_haiku(int category){
    
    int q=access_queue();
    char fileName[MAX];
    int count=0;
    
    if (category==JAP){
        strcpy(fileName, "japanese.txt");
        // count=JAP;
    }else{
        strcpy(fileName, "western.txt");
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
        printf("%d)- %s\n",count,line);
        n_haiku[category-1]++;
        
    }

    fclose(file);
    printf("Haikus of type %d are written!\n",category);
    // return NULL;
}

void main_signal_handler(int signum){
    if(signum==18){
        exit(1);
    }else{
        printf("signal:: %d",signum);
        printf("---------\n");
        for(int i=0;i<4;i++){
            printf("proc:: %d\n",thread_arr[i]);
            kill(thread_arr[i],signum);
        }
        printf("---------\n");
        return;
    }
    
}

void writer_signal_handler(int signum){
    printf("in writer %d\n",signum);
    // int cat;
    // for (int i=0;i<2;i++){
    //     if(signum==matr[i][0]){
    //         cat=matr[i][1];
    //         if(n_haiku[cat-1]==0){
    //             printf("Category is %d\n",matr[i][1]);
    //             write_haiku(cat);
    //         }
    //         return;
    //     }
    // }
    // printf("Incorrect Signal!\n");

}

void reader_signal_handler(int signum){
    int cat;
    int q_id=access_queue();
    char haiku[MAX];
    printf("in reader %d\n",signum);
    printf("---------\n");
    for(int i=0;i<4;i++){
        printf("proc:: %d\n",thread_arr[i]);
        // kill(thread_arr[i],signum);
    }
    printf("---------\n");
    // for (int i=0;i<2;i++){
    //     if(signum==matr[i][0]){
    //         // flag--;
    //         cat=matr[i][1];
    //         printf("Category is %d\n",cat);
    //         read_queue(q_id,haiku,cat);
    //         printf("cat ::%d ---------\n- %s",cat,haiku);
    //         n_haiku[cat-1]--;
    //         return;
    //     }
    // }
    // printf("Incorrect Signal!\n");


}

void* writer_thread(void* category){
    int *i=(int*)category;
    int x=*i;
    printf("writer:: %d\n",*i);
    int cat=matr[x][1];
    int p=getpid();
    printf("category writer:: %d\n",cat);
    thread_arr[x]=p;
    int count=100;

    if (signal(SIGQUIT, writer_signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, writer_signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}
    
    while(count){
        sleep(1);
        // count--;
        printf("waiting...\n");
    }
    pthread_exit(NULL);
}



void* reader_thread(void* category){

    int *i=(int*)category;
    int x=*i;
    printf("reader:: %d\n",x);
    int cat=matr[x-2][1];
    printf("category reader:: %d\n",cat);

    int p=getpid();
    thread_arr[x]=p;
    int count=100;

    if (signal(SIGQUIT, reader_signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, reader_signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}

    while(count){
        sleep(1);
        printf("...waiting\n");
        // count--;
    }
    pthread_exit(NULL);
}


int main(){


    int p=getpid();
    int seg=create_segment();
    write_values(seg,p);
    pthread_t tid [2] ; 
    int q_id=create_queue();
    n_haiku[0]=0;
    n_haiku[1]=0;
    int arr[4]={0,1,2,3};
    int cat_arr[2]={1,2};
    printf("Process:: %d\n\n",p); 

    if (signal(SIGQUIT, main_signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, main_signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}
    if (signal(SIGTSTP, main_signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}


    int i;
    for(i=0;i<4;i++){
        // puts("create thread");
        if(i<2){
            if (pthread_create (&tid [i], NULL, &writer_thread, (void*) &(arr[i])) == -1){
                // error ("pthread_create") ;
                puts("COULDNT CREATE");
                return -1;
            }
        }else{
            if (pthread_create (&tid [i], NULL, &reader_thread, (void*) &(arr[i])) == -1){
                // error ("pthread_create") ;
                puts("COULDNT CREATE");
                return -1;
            }  
        }
    }

    ///////////////// JOIN
    for(int i=0;i<4;i++){
        // puts("join thread");
        if (pthread_join (tid [i], NULL) == -1){
            // error ("pthread_join") ;
            puts("COULDNT JOIN");
            return -1;
        }   
    }
    
    remove_segment(seg);

    remove_queue(q_id);
    puts("end of server");
    return 0;
}