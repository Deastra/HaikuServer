#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 255
typedef struct message
{
  long mtype ;
  char arr[MAX];
} message;

void send_error(char *str){
    if (strcmp(str," ftok ")==0){
        printf("FTOK\n");
    }else if(strcmp(str," msgget ")==0){
        printf("GET\n");
    }else if(strcmp(str," msgsnd ")==0){
        printf("SND\n");
    }else if(strcmp(str," msgrcv ")==0){
        printf("RCV\n");
    }else if(strcmp(str," shmdt ")==0){
        printf("DT\n");
    }else if(strcmp(str," shmat read ")==0){
        printf("READ\n");
    }else{
        printf("ERROR\n");
    }
}

int access_queue ( void )
{
    key_t k ;
    int id ;
    k = ftok ("/etc/passwd", 'A') ;
    if (k == -1){
        send_error (" ftok ") ;}
    id = msgget (k, 0) ;
    if (id == -1){
        send_error (" msgget ") ;}
    return id ;
}

int create_queue ( void ){
    key_t k ;
    int id ;
    k = ftok ("/etc/passwd", 'A') ;
    if (k == -1){
        send_error (" ftok ") ;}
    id = msgget (k, IPC_CREAT | 0666) ;
    if (id == -1){
        printf("id_error\n");
        send_error (" msgget ") ;}

    return id ;
}

void write_queue ( int id , char h_arr[], int priority){
    message m ; int r ;
    m.mtype = priority ;
    strcpy(m.arr,h_arr);
    printf("before\n");
    r = msgsnd (id , &m, sizeof m - sizeof m.mtype , 0) ;
    printf("after\n");
    if (r == -1) {send_error (" msgsnd ") ;}
    
}

void read_queue ( int id,char arr[],int priority)
{
    message m ; int r, val ;

    r = msgrcv (id , &m, sizeof m - sizeof m.mtype , priority, 0) ;
    if (r == -1){
        send_error (" msgrcv ") ;
    }
    strcpy(arr,m.arr);    
}

void remove_queue ( int id )
{
    int r ;
    r = msgctl (id , IPC_RMID , NULL ) ;
}

// void send(int prior,int size){
//     int queue_id=access_queue();
//     write_queue(queue_id,size,prior);
// }

// int get(int prior){
//     int queue_id=access_queue();
//     int signum=read_queue(queue_id,prior);
//     return signum;
// }