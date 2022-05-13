#ifndef RWT
#define RWT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "shdmemory.h"
#include "msgqueue.h"

#define JAP 1
#define WEST 2
#define MAX 255
int matr[2][2]={ {2,JAP} , {3,WEST} };
int flag=1;
int n_haiku[2];

void write_haiku(int category);
void* writer_thread(void* category);
void* reader_thread(void* category);
void add_thread(int category);

#endif