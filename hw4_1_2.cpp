#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>

std::vector<int> count(3);
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
int finish = 0;

void* count_numbers_0(void* data){
    std::string s = *( (std::string*) data );
    pthread_mutex_lock(&count_mutex);
    for(int i = 0 ; i < (int) s.size() ; i++) count[s[i]-'0']++;
    finish++;
    pthread_mutex_unlock(&count_mutex);
    
    while(finish != 3) ;
    std::cout << "0: " << count[0] << "\n";
    pthread_mutex_unlock(&mutex_0);

    pthread_exit(NULL);
}

void* count_numbers_1(void* data){
    std::string s = *( (std::string*) data );
    pthread_mutex_lock(&count_mutex);
    for(int i = 0 ; i < (int) s.size() ; i++) count[s[i]-'0']++;
    finish++;
    pthread_mutex_unlock(&count_mutex);

    pthread_mutex_lock(&mutex_0);
    std::cout << "1: " << count[1] << "\n";
    pthread_mutex_unlock(&mutex_1);

    pthread_exit(NULL);
}

void* count_numbers_2(void* data){
    std::string s = *( (std::string*) data );
    pthread_mutex_lock(&count_mutex);
    for(int i = 0 ; i < (int) s.size() ; i++) count[s[i]-'0']++;
    finish++;
    pthread_mutex_unlock(&count_mutex);

    pthread_mutex_lock(&mutex_1);
    std::cout << "2: " << count[2] << "\n";
    pthread_mutex_unlock(&mutex_2);

    pthread_exit(NULL);
}

std::vector<std::string> split(std::string str, int size){
    std::vector<std::string> split_str;
    int now = 0;
    while(now < (int) str.size()){
        std::string tmp;
        for(int i = now ; i < now + size ; i++) tmp += str[i];
        split_str.push_back(tmp);
        now += size;
    }

    return split_str;
}

int main(){
    const int n = 3;
    int len;
    std::cin >> len;
    std::string str;
    std::cin >> str;

    int size = len / n;
    std::vector<std::string> split_str = split(str, size);

    pthread_t tids[n];
    pthread_mutex_lock(&mutex_0);
    pthread_mutex_lock(&mutex_1);
    pthread_mutex_lock(&mutex_2);
    pthread_create(&tids[0], NULL, &count_numbers_0, (void*) &split_str[0]);
    pthread_create(&tids[1], NULL, &count_numbers_1, (void*) &split_str[1]);
    pthread_create(&tids[2], NULL, &count_numbers_2, (void*) &split_str[2]);
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);
    pthread_join(tids[2], NULL);

    return 0;
}