#ifndef HW
#define HW

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "msgqueue.c"

#define JAP 6
#define WEST 9

#define CJAP 1
#define CWEST 2
int cat_arr[2]={CWEST,CJAP};

void write_haiku(int category);
void* haiku_write_thread(void* category);
int haiku_writer();

#endif
