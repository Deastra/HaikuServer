#ifndef HW
#define HW

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "msgqueue.c"

#define JAP 1
#define WEST 2

int cat_arr[2]={JAP,WEST};

void write_haiku(int category);
void* haiku_write_thread(void* category);
int haiku_writer();

#endif
