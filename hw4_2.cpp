#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int point;
int in_circle = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

bool is_in_circle(float x, float y){
    float diff_2 = x*x + y*y;
    return diff_2 < 1;
}

void* sample_point(void* size_ptr){
    int size = *((int*) size_ptr);
    srand(time(NULL));
    for(int i = 1 ; i <= size ; i++){
        float x = ( (float) rand() / (float) RAND_MAX ) * 2 - 1;
        float y = ( (float) rand() / (float) RAND_MAX ) * 2 - 1;
        if(is_in_circle(x, y)){
            pthread_mutex_lock(&mutex);
            in_circle++;
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(NULL);
}

int main(){
    int n;
    std::cin >> n;
    std::cin >> point;
    int size = point / n;
    
    pthread_t tids[n];
    for(int i = 0 ; i < n ; i++)
        pthread_create(&tids[i], NULL, &sample_point, (void*) &size);

    for(int i = 0; i < n; i++)
        pthread_join(tids[i], NULL);

    float pi = 4 * ((float) in_circle / (float) point);
    std::cout << "get: " << in_circle << "\n";
    std::cout << "Pi: " << pi << "\n";

    return 0;
}