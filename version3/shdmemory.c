#include "shdmemory.h"

void send_error(char *str){
    if (strcmp(str," ftok ")){
        printf("FTOK\n");
    }    else if(strcmp(str," shmget ")){
        printf("GET\n");
    }else if(strcmp(str," shmctl ")){
        printf("CTL\n");
    }else if(strcmp(str," shmat write ")){
        printf("WRITE\n");
    }else if(strcmp(str," shmdt ")){
        printf("DT\n");
    }else if(strcmp(str," shmat read ")){
        printf("READ\n");
    }else{
        printf("ERROR\n");
    }
}

int create_segment ( void ){
    key_t k ;
    int id ;
    k = ftok ("/etc/passwd", 'M') ;
    if (k == -1){
        send_error (" ftok ") ;}
    id = shmget (k, 4096 , IPC_CREAT | 0666) ;
    if (id == -1){
        send_error (" shmget ") ;}
    return id ;
}

int access_segment ( void ){
    key_t k ;
    int id ;
    k = ftok ("/etc/passwd", 'M') ;
    if (k == -1){
    send_error (" ftok ") ;}
    id = shmget (k, 0, 0) ;
    if (id == -1){
    send_error (" shmget ") ;}
    return id ;
}

void remove_segment ( int id ){
    int r ;
    r = shmctl (id , IPC_RMID , NULL ) ;
    if (r == -1){
    send_error (" shmctl ") ;}
}

void write_values ( int id , int cat ){
    int * addr ;
    addr = shmat (id , NULL , 0) ;
    if ( addr == ( void *) -1 ){
    send_error (" shmat write ") ;}
    addr[0]=cat;
    if ( shmdt ( addr ) == -1){
    send_error (" shmdt ") ;}
}

void read_values ( int id , int *cat){
    int * addr ;
    addr = shmat (id , NULL , 0) ;
    if ( addr == ( void *) -1){
    send_error (" shmat read ") ;}
    *cat=addr[0];
    if ( shmdt ( addr ) == -1){
    send_error (" shmdt ") ;}
}
