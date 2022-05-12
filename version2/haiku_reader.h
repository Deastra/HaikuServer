#ifndef HR
#define HR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "msgqueue.c"

// categories
#define JAP 1
#define WEST 2

//array of categories
int cat_arr[2]={JAP,WEST};

void read_haiku(int category);
void* haiku_read_thread(void* category);
int haiku_reader();

#endif


