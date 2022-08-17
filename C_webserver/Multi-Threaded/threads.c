#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define THREAD_NUM 4


struct args {
    int height;
    char *http;
    int response_len;
};

//Testing Thread's Routine 
void* threadTestRoutine(void *input) {
    printf("Hello from threads %d \n", ((struct args*)input)->height);
    printf("fd %s \n", ((struct args*)input)->http);
    sleep(3);
    printf("Ending thread%d \n",((struct args*)input)->response_len);
}


int main(int argc, char* argv[]) {
    char response [100000] = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 100000\n\n ";

    struct args *Allen = (struct args *)malloc(sizeof(struct args));
    Allen->height = 15;
    Allen->http = response;
    Allen->response_len = strlen(response);

    int i = 0;
    pthread_t th[THREAD_NUM];


    pthread_create(&th[i++], NULL, &threadTestRoutine, (void *)Allen);
    
    if (i >=3)
    {
        i = 0;
        while(i < 50)
        {
        pthread_join(th[i++],NULL);
        }    
    }

    pthread_create(&th[i++], NULL, &threadTestRoutine, (void *)Allen);

    if (i >=3)
    {
        i = 0;
        while(i < 50)
        {
        pthread_join(th[i++],NULL);
        }    
    }

    pthread_create(&th[i++], NULL, &threadTestRoutine, (void *)Allen);

    if (i >=3)
    {
        i = 0;
        while(i < 50)
        {
        pthread_join(th[i++],NULL);
        }    
    }



    

    return 0;
}





