
#include "all/read_write_thread.c"



// int server();
void signal_handler(int signum);

int server();


int main(){
    if(server()==-1){
        puts(" ------- !!! Server Error !!! ------- \n");
    }
    return 0;
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
    return 1;
}

void signal_handler(int signum){
    flag++;
    int cat;
    if(signum==SIGTSTP){
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
