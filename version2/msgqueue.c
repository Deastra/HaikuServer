#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct message
{
  long mtype ;
  char *arr[3];
} message;

void send_error(char *str){
    if (strcmp(str," ftok ")){
        printf("FTOK\n");
    }    else if(strcmp(str," msgget ")){
        printf("GET\n");
    }else if(strcmp(str," msgsnd ")){
        printf("SND\n");
    }else if(strcmp(str," msgrcv ")){
        printf("RCV\n");
    }else if(strcmp(str," shmdt ")){
        printf("DT\n");
    }else if(strcmp(str," shmat read ")){
        printf("READ\n");
    }else{
        printf("ERROR\n");
    }
}

int access_queue ( void )
{
  key_t k ;
  int id ;
  k = ftok ("/etc/passwd", 'F') ;
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
    k = ftok ("/etc/passwd", 'F') ;
    if (k == -1){
        send_error (" ftok ") ;}
    id = msgget (k, IPC_CREAT | 0666) ;
    if (id == -1){
        printf("id_error\n");
        send_error (" msgget ") ;}
    return id ;
}

void write_queue ( int id , char **h_arr, int priority)
{
    struct message m ; int r ;
    m.mtype = priority ;
    for(int i=0;i<3;i++){
        m.arr[i]=(char*)malloc(sizeof(char)*255);
        strcpy(m.arr[i],h_arr[i]);
    }
    r = msgsnd (id , &m, sizeof m - sizeof m.mtype , 0) ;
    if (r == -1) {send_error (" msgsnd ") ;}
}


void read_queue ( int id,char **arr,int priority)
{
    struct message m ; int r, val ;
    for(int i=0; i<3;i++){
        arr[i]=(char*)malloc(sizeof(char)*255);
        strcpy(arr[i],m.arr[i]);
    }
    r = msgrcv (id , &m, sizeof m - sizeof m.mtype , priority, 0) ;
    if (r == -1){
    send_error (" msgrcv ") ;}
    
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