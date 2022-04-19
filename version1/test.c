#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    srand(time(NULL));
    int count=10;
    while(count>0){
        printf("%d\n",rand()%5);
        count--;
    }

}