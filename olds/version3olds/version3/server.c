#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all/shdmemory.c"
#include "all/msgqueue.c"
#include <unistd.h>
#include <signal.h>

#define JAP 1
#define WEST 2

// getsignal
// choose category
// write haiku of that category
int flag=1;
int matr[2][2]={ {2,JAP} , {3,WEST} };
int n_jap=0;
int n_west=0;


int get_queue_state(int category){
    int seg=access_segment();
    int arr[3];
    read_values(seg,arr);
    // if((category==JAP && arr[JAP]==0) || (category==WEST && arr[WEST]==0)){
    //     return 0;
    // }else{
    //     return 1;
    // }

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
    
    char line[255];
    int length=0;
    
    while(fgets(line, sizeof(line), file)!=NULL) {
        
        length = strlen(line);
        line[length - 1] = '\0';

        write_queue(q,line,category);
        count_haiku++;
    }
    
    arr[category]=count_haiku;
    write_values(seg,arr);
    fclose(file);
    // return NULL;
}


void signal_handler(int signum){
    // int q_id=access_queue();
    int cat;

    for (int i=0;i<2;i++){
        if(signum==matr[i][0]){
            printf("Category is %d\n",matr[i][1]);
            cat=matr[i][1];
            if(!get_queue_state(cat)){
                write_haiku(cat);
            }
            return;
        }
    }
    printf("Incorrect Signal!\n");
}

int main(){
    int seg=create_segment();
    int p_id=getpid();
    int arr[3]={p_id,0,0};

    write_values(seg,arr);

    printf("Process:: %d\n\n",p); 

    if (signal(SIGQUIT, signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n");}
    if (signal(SIGINT, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n");}


    while(1){
        sleep(2);
    }

    remove_segment();

}