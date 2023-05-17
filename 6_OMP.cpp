#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#define CAPACITY 10
std::vector<int> v;
int storage[CAPACITY] = {};
omp_lock_t lock;
int current = 0; //current last element

void producer();

void consumer();

int main() {
    srand(time(NULL));

    omp_init_lock(&lock);

    printf("Producer-consumer\n\n");
    printf("The simulation has begun. Press Ctrl+C to exit.\n");
#pragma omp parallel sections num_threads(2)  // Create two parallel threads.
    {
#pragma omp section
        {
            producer();
        }
#pragma omp section
        {
            consumer();
        }
    }
}

void producer() {
    while (true) {
        omp_set_lock(&lock);
        if (v.size()<10) {
            v.push_back( abs(rand()%100));
            printf("Create product %d %zu\n", v.back(),v.size());
        } else
            printf("Storage is full invoked by prod\n");

        omp_unset_lock(&lock);
        sleep(1); //sleep(rand() % 5);
    }
}

void consumer() {
    while (true) {
        omp_set_lock(&lock);
        if (!v.empty()) {
            int tmp=v.back();
            v.pop_back();
            printf("Get product %d %d\n",tmp, current);
        } else
            printf("Storage is empty invoked from consumer\n");

        omp_unset_lock(&lock);
        sleep(1); //sleep(rand() % 5);
    }
}
