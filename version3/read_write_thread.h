#ifndef RWT
#define RWT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define JAP 1
#define WEST 2
#define MAX 255


void write_haiku(int category);
void* writer_thread(void* category);
void* reader_thread(void* category);
void add_thread(int category);
int server();
void signal_handler(int signum);



#endif 
