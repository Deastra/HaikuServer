#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "msgqueue.c"

int main(){
    int q=access_queue();
    remove_queue(q);
}

