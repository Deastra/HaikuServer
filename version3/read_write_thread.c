#include "read_write_thread.h"
#include "shdmemory.h"
#include "msgqueue.h"

int flag=1;
int matr[2][2]={ {2,JAP} , {3,WEST} };
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
    for(int i=0;i<10;i++){
        line[i]='a';
    }

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



int server(){
    int p=getpid();
    int seg=create_segment();
    write_values(seg,p);
    
    int q_id=create_queue();
    n_haiku[0]=0;
    n_haiku[1]=0;
    printf("Process:: %d\n\n",p); 

    if (signal(SIGQUIT, signal_handler) == SIG_ERR){
        perror("can't catch SIGQUIT\n"); return -1;}
    if (signal(SIGINT, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n"); return -1;}
    if (signal(SIGTSTP, signal_handler) == SIG_ERR){
        perror("can't catch SIGINT\n"); return -1;}

    while(flag){
        sleep(1);
        printf("waiting %d...\n",flag);
    }
    
    remove_segment(seg);
    remove_queue(q_id);
    puts("End of Server");
    return 0;
}

void signal_handler(int signum){
    flag++;
    int cat;
    if(signum==SIGTSTP){
        flag=0;
        
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



