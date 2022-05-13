#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all/shdmemory.c"
#include "all/msgqueue.c"
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#define JAP 1
#define WEST 2 

// getsignal
// choose category
// write haiku of that category
int flag=1;
int matr[2][2]={ {2,JAP} , {3,WEST} };
int n_jap=0;
int n_west=0;
int tflag[2]={0,0};

pthread_t tid [2] ;




int get_queue_state(int category){
    int seg=access_segment();
    int arr[3];
    read_values(seg,arr);
    // if((category==JAP && arr[JAP]==0) || (category==WEST && arr[WEST]==0)){
    //     return 0;
    // }else{
    //     return 1;
    // }
    printf("Que State:: %d %d\n",arr[1],arr[2]);
    if(arr[category]==0){
        return 0;
    }else{
        return 1;
    }
}

void write_haiku(int category){
    
    int q=access_queue();
    char fileName[MAX];
    // int count;
    
    // for number of haikus left or written
    int seg=access_segment();
    int arr[3];
    read_values(seg,arr);
    int count_haiku=0;
    ////////////////////////

    if (category==JAP){
        strcpy(fileName, "all/japanese.txt");
    }else{
        strcpy(fileName, "all/western.txt");
    }

    FILE* file = fopen(fileName, "r"); 
    puts("got file");
    char line[255];
    int length=0;
    printf("------ For Category %d ------\n",category);
    while(fgets(line, sizeof(line), file)!=NULL) {
        length = strlen(line);
        line[length - 1] = '\0';
        printf("%d ) %s \n",count_haiku+1,line);
        write_queue(q,line,category);
        puts("wrote queue");
        count_haiku++;
    }
    tflag[category-1]=1;
    
    arr[category]=count_haiku;
    puts("almost end writing");
    write_values(seg,arr);
    printf("wrote values segment %d %d\n",arr[1],arr[2]);
    fclose(file);
    printf("Finished writing\n");
    // return NULL;
}

void* thread_func(void* category){
    puts("in thread");
    int *cat=(int*)category;
    
    puts("go writing");
    write_haiku(*cat);

    pthread_exit(NULL);
}

int thread_add(int cat){
    ///////////////// CREATE
    if(!get_queue_state(cat)){
        for(int i=0;i<2;i++){
            if(i==cat-1){
                puts("passed state test");
                if (pthread_create (&tid [i], NULL, &thread_func, (void*) &(cat)) == -1){
                    // error ("pthread_create") ;
                    puts("COULDNT CREATE");
                    return -1;
                }
                if (pthread_join (tid [i], NULL) == -1){
                    // error ("pthread_join") ;
                    puts("COULDNT JOIN");
                    return -1;
                }   
                break;
            }
        }
    }else{
        printf("queue of category %d is not empty\n",cat);
    }
    return 0;

}

void signal_handler(int signum){
    // int q_id=access_queue();
    int cat;
    printf("signal:: %d\n  ",signum);
    for (int i=0;i<2;i++){
        if(signum==matr[i][0]){
            printf("Category is %d\n",matr[i][1]);
            cat=matr[i][1];
            if(thread_add(cat)==-1){printf("ERROR in threads\n");}
            printf("end of signal\n");
            return;
        }
    }
    printf("Incorrect Signal!\n");
}

void sighand(int sig){
    for (int i=0;i<2;i++){
        if(sig==matr[i][0]){
            printf("%d %d\n",sig,matr[i][1]);
        }
    }
}

int main(){
    int seg=create_segment();
    int p_id=getpid();
    int arr[3]={p_id,0,0};

    write_values(seg,arr);

    printf("Process:: %d\n\n",p_id); 

    if (signal(SIGQUIT, signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}

    int waittime=20;
    while(waittime){
        sleep(2);
        printf("waiting in while...\n");
        read_values(seg,arr);
        printf("number of left:: %d %d\n",arr[1],arr[2]);
        waittime--;
    }


    printf("end of while\n");
    remove_segment(seg);
    printf("end of server\n");
}