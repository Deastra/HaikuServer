#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "shdmemory.c"
int main(){
    int seg=access_segment();
    int arr[3];
    read_values(seg,arr);
    remove_segment(seg);
    kill(arr[0],9);

    return 0;
}