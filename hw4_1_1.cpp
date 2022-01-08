#include <iostream>
#include <vector>
#include <string>
#include <pthread.h>

std::vector<int> count(3);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* count_numbers(void* data){
    std::string s = *( (std::string*) data );
    pthread_mutex_lock(&mutex);
    for(int i = 0 ; i < (int) s.size() ; i++) count[s[i]-'0']++;
    pthread_mutex_unlock(&mutex);
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
    int n;
    std::cin >> n;
    int len;
    std::cin >> len;
    std::string str;
    std::cin >> str;

    int size = len / n;
    std::vector<std::string> split_str = split(str, size);

    pthread_t tids[n];
    for(int i = 0 ; i < n ; i++)
        pthread_create(&tids[i], NULL, &count_numbers, (void*)&split_str[i]);

    for(int i = 0; i < n; i++)
        pthread_join(tids[i], NULL);

    for(int i = 0 ; i < 3 ; i++) std::cout << i << ": " << count[i] << "\n";
}