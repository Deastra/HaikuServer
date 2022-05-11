#include "haiku_writer.h"

// int main(){
//     if (haiku_writer()==-1){
//         printf("Reader couldn't be executed!\n");
//     }
//     return 0;
// }

void write_haiku(int category){
    
    int q=access_queue();
    char fileName[MAX];
    int count;
    
    if (category==CJAP){
        strcpy(fileName, "japanese.txt");
        count=JAP;
    }else{
        strcpy(fileName, "western.txt");
        count=WEST;
    }

    FILE* file = fopen(fileName, "r"); 
    
    char line[255];
    int length=0;

    while(fgets(line, sizeof(line), file)!=NULL) {
        
        length = strlen(line);
        line[length - 1] = '\0';
        write_queue(q,line,category);
    }

    fclose(file);
    printf("Haikus of type %d are written!\n",category);
    // return NULL;
}

void* haiku_write_thread(void* category){
    int* cat=(int*) category;
    write_haiku(*cat);
    pthread_exit(NULL);
    // return NULL;
}

int haiku_writer (){
    
    pthread_t tid [2] ; 
    int cat1=1,cat2=2;

    ///////////////// CREATE
    for(int i=0;i<2;i++){
        if (pthread_create (&tid [i], NULL, &haiku_write_thread, (void*) &(cat_arr[i])) == -1){
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

    return 1;

}
