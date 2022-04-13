#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// #include <pthread.h>
#include "msgqueue.c"
// #define MAX 10

// int arr_global[]={1,2,3,4,5,6};
// works
// int count=20;
// int count1=20;
// int count2=20;

// void *function_write (void *arg){
//     char **arr=(char**)arg;
//     int q=create_queue();
//     write_queue(q,arr,1);

//     //works
//     // while(count1>0){
//     //     sleep(2);
//     //     printf("THREAD 1\n");
//     //     arr[0]=99;
//     //     count1--;
//     // }

    
//     return NULL ;
// }

// void *function_read (void *arg){
//     // char **arr=(char**)arg;
//     char *arr[3];
//     int q=access_queue();
//     read_queue(q,arr,1);
//     remove_queue(q);
    
//     for (int i=0;i<3;i++){
//         printf("%d) %s \n",i,arr[i]);
//     }
//     // works
//     // while(count2>0){
//     //     sleep(2);
//     //     printf("THREAD 2\n"); 
//     //     arr[0]=100;
//     //     count2--;
//     // }
    
//     return NULL ;
// }

// // works
// // void *function(void *arg){
// //     int *arr=(int*)arg;
// //     // int q=access_queue();
// //     // read_queue(q,arr,);
// //     while(count>0){
// //         printf("array[0]:: %d\n",arr[0]);
// //         sleep(2);
// //         count--;
// //     }
// //     return NULL ;
// // }

// void error (char *msg){
//     perror (msg) ; exit (1) ;
// }

// int main (int argc, char *argv []){
//     int a[]={1,2,3};
//     char *h[]={"Haik1","Haik2","Haik3"};
//     pthread_t tid [3] ; 
//     char *read[3];
//     ///////////////// CREATE
//     if (pthread_create (&tid [0], NULL, &function_write, (void *) h) == -1){
//         error ("pthread_create") ;
//     }
//     if (pthread_create (&tid [1], NULL, &function_read, NULL) == -1){
//         error ("pthread_create") ;
//     }
//     // if (pthread_create (&tid [2], NULL, &function, (void *) &a) == -1){
//     //     error ("pthread_create") ;
//     // }
    

//     ///////////////// JOIN
//     if (pthread_join (tid [0], NULL) == -1){
//         error ("pthread_join") ;
//     }    
//     if (pthread_join (tid [1], NULL) == -1){
//         error ("pthread_join") ;
//     }
//     // if (pthread_join (tid [2], NULL) == -1){
//     //     error ("pthread_join") ;
//     // }
    
// }


int main(){
    int q=access_queue();
    remove_queue(q);

}

