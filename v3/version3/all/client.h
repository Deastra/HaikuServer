#ifndef CL
#define CL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "shdmemory.c"
#include "msgqueue.c"

void signal_handler(int signum);
int client();

#endif