#ifndef SHD
#define SHD

#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>

void send_error(char *str);
int create_segment ( void );
int access_segment ( void );
void remove_segment ( int id );
void write_values ( int id , int cat );
void read_values ( int id , int *cat);


#endif 