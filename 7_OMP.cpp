#include<stdio.h>
#include<omp.h>
#include<string.h>
#include <csignal>
#include <time.h>
#include <cstdlib>

void writer(char *buf1, omp_lock_t *writelock);

void reader(char *buf1, omp_lock_t *writelock);

int main() {


    char buf1[100];
    strcpy(buf1, "hi");
    int i;
    omp_set_num_threads(4);
    omp_lock_t writelock;

    omp_init_lock(&writelock);
#pragma omp parallel sections num_threads(4)  // Create two parallel threads.
    {
#pragma omp section
        {
            writer(buf1, &writelock);
        }
#pragma omp section
        {
            reader(buf1, &writelock);
        }
#pragma omp section
        {
            reader(buf1, &writelock);
        }
#pragma omp section
        {
            reader(buf1, &writelock);
        }
    }
}

void writer(char *buf1, omp_lock_t *writelock) {
    while (true) {
        printf("\nI am THREAD:%d writing", omp_get_thread_num());
        omp_set_lock(writelock);
        strcat(buf1, "qwerty");
        omp_unset_lock(writelock);
        sleep(3+rand()%3);
    }
}

void reader(char *buf1, omp_lock_t *writelock) {
    while (true) {
        omp_set_lock(writelock);
        printf("\nI am THREAD:%d reading", omp_get_thread_num());
        printf("\nthe buffer contents are:\n %s", buf1);
        omp_unset_lock(writelock);
        sleep(3+rand()%2);
    }
}
