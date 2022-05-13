#include "shdmemory.h"
#include "msgqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int q=access_queue();
    int seg=access_segment();
    remove_queue(q);
    remove_segment(seg);
    return 0;
}