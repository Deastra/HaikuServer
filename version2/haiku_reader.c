#include "haiku_reader.h"

int main(){
    if (haiku_reader()==-1){
        printf("Reader couldn't be executed!\n");
    }
    return 0;
}

void read_haiku(int category){
    
    int q=access_queue();
    puts("IN FUNCTION READER\n");
    char arr[MAX];
    
    for(int i=0;i<3;i++){
        read_queue(q,arr,category);   
        printf("category:: %d\n%d) %s \n",category,i,arr); 
    }

    printf("HAIKUS WERE READ!\n");
    printf("################\n");
    
}

void* haiku_read_thread(void* category){
    int *cat=(int*)category;
    read_haiku(*cat);
    pthread_exit(NULL);
}

int haiku_reader (){
    
    pthread_t tid [2] ; 
    
    int q=create_queue();
    
    /////////////// CREATE
    for(int i=0;i<2;i++){
        if (pthread_create (&tid [i], NULL, &haiku_read_thread, (void*) &(cat_arr[i])) == -1){
            // error ("pthread_create") ;
            puts("COULDNT CREATE");
            return -1;
        }
    }

    ///////////////// JOIN
    for(int i=0;i<2;i++){
        if (pthread_join (tid [i], NULL) == -1){
            // error ("pthread_join") ;
            puts("COULDNT JOIN");
            return -1;
        }  
    } 

    remove_queue(q);
    return 1;

}
