// SO IS1 210B LAB11
// Stanislav Tkachenko
// ts54948@zut.edu.pl
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define N 1000000
#define W 3

float sum_threads = 0.0;
HANDLE mutex;

typedef struct
{
    int start;
    float *array;
    float part_sum;
    int end;
} Thread;

void print_error_and_exit(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void validate_args(int argc, char *argv[], const int n, const int w)
{
    for (int i = 0; i < strlen(argv[1]); i++)
        if (argv[1][i] < '0' || argv[1][i] > '9')
            print_error_and_exit("Invalid argument. Sequence must be entirely from decimal numbers.");

    if ((0 >= n || n >= N) || (0 >= w || w >= n) || (argc != W))
        print_error_and_exit("Invalid arguments. Arguments must be 2 numbers.");
}

DWORD WINAPI compute_sum(LPVOID arg)
{
    Thread *thread = (Thread *)arg;

    printf("Thread #%x size=%d\n", GetCurrentThreadId(), thread->end - thread->start);

    for (int i = thread->start; i < thread->end; i++)
        thread->part_sum += thread->array[i];

    WaitForSingleObject(mutex, INFINITE);
    sum_threads += thread->part_sum;
    ReleaseMutex(mutex);

    printf("Thread #%x start=%d end=%d sum=%f\n", GetCurrentThreadId(), thread->start, thread->end, thread->part_sum);

    return 0;
}

int main(int argc, char *argv[])
{
    const int w = atoi(argv[2]);
    const int n = atoi(argv[1]);

    validate_args(argc, argv, n, w);

    float *t = (float *)malloc(n * sizeof(float));

    srand(0);
    for (int i = 0; i < n; i++)
        t[i] = 1000. * rand() / RAND_MAX;

    Thread thread[100];
    HANDLE threads[100];

    int remaining = n % w;
    int cur_start = 0;
    int size = n / w;

    HANDLE mutex = CreateMutex(NULL, FALSE, NULL);

    LARGE_INTEGER t1, t2, fr;
    QueryPerformanceCounter(&t1);

    for (int i = 0; i < w; i++)
    {
        thread[i].start = cur_start;
        thread[i].array = t;
        thread[i].part_sum = 0.0;
        thread[i].end = cur_start + size + (i == w - 1 ? remaining : 0);

        threads[i] = CreateThread(NULL, 0, compute_sum, (LPVOID)&thread[i], 0, NULL);

        cur_start = thread[i].end;
    }

    WaitForMultipleObjects(w, threads, TRUE, INFINITE);

    QueryPerformanceCounter(&t2);
    QueryPerformanceFrequency(&fr);

    double time_threads = (t2.QuadPart - t1.QuadPart) / (double)fr.QuadPart;
    //
    // ----------------------------------------------------------------------------
    //
    QueryPerformanceCounter(&t1);

    float sum_no_threads = 0.0;
    for (int i = 0; i < n; i++)
        sum_no_threads += t[i];

    QueryPerformanceCounter(&t2);
    QueryPerformanceFrequency(&fr);

    double time_no_threads = (t2.QuadPart - t1.QuadPart) / (double)fr.QuadPart;
    //
    // ----------------------------------------------------------------------------
    //
    printf("w/Threads sum=%f, time=%fsec\n", sum_threads, time_threads);
    printf("wo/Threads sum=%f, time=%fsec\n", sum_no_threads, time_no_threads);

    CloseHandle(mutex);
    free(t);

    return EXIT_SUCCESS;
}