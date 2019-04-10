#include <pthread.h>
#include <stdio.h>
#define MAX 16
#define MAX_THREAD 4

int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 };
int sum[4] = { 0 };
int part = 0;

void* sum_array(void* arg)
{

    int thread_part = part++;

    for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++)
        sum[thread_part] += a[i];
}


int main()
{
    clock_t time;
    time = clock();
    pthread_t threads[MAX_THREAD];


    for (int i = 0; i < MAX_THREAD; i++)
        pthread_create(&threads[i], NULL, sum_array, (void*)NULL);


    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);


    int total_sum = 0;
    for (int i = 0; i < MAX_THREAD; i++)
        total_sum += sum[i];

    printf("sum is %d\n ", total_sum);
    time = clock() - time;
    printf("time is %f\n", (double)time/CLOCKS_PER_SEC);

    return 0;
}
