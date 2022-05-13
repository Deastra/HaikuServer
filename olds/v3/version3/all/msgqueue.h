#ifndef MSG
#define MSG

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

void send_qerror(char *str);
int access_queue ( void );
int create_queue ( void );
void write_queue ( int id , char h_arr[], int priority);
void read_queue ( int id,char arr[],int priority);
void remove_queue ( int id );

#endif