#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>

// gcc lab_8.c -o lab_8
// ./lab_8 98765

void print_error_and_exit(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void validate_args_count(int argc, char *argv[])
{
    if (argc != 2 || strlen(argv[1]) > 25)
        print_error_and_exit("Invalid argument. Sequence must be 1-25 numbers length.");
}

void validate_args_are_decimal(char *argv[])
{
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
            print_error_and_exit("Invalid argument. Sequence must be entirely from decimal numbers.");
    }
}

void if_args_len_is_one_exit_with_arg(char *argv[])
{
    if (strlen(argv[1]) == 1)
    {
        int result = argv[1][0] - '0';
        exit(result);
    }
}

void validate_args_properties(int argc, char *argv[])
{
    validate_args_count(argc, argv);
    validate_args_are_decimal(argv);
    if_args_len_is_one_exit_with_arg(argv);
}

char *get_error_message(const int cn)
{
    char message[] = "Error with fork() for first child.";
    if (cn == 2)
    {
        char message[] = "Error with fork() for second child.";
    }

    return message;
}

void run_proccess(pid_t c, char *half, char *argv[], const int cn)
{
    if (c == -1)
    {
        char *message = get_error_message(cn);
        print_error_and_exit(message);
    }
    else if (c == 0)
    {
        execl(argv[0], argv[0], half, (char *)NULL);

        char *message = get_error_message(cn);
        print_error_and_exit(message);
    }
}

int main(int argc, char *argv[])
{
    validate_args_properties(argc, argv);

    int n = strlen(argv[1]);
    int half = n / 2;
    char first_half[half + 1];
    char second_half[n - half + 1];

    // printf("%d %d %d\n", n, half + 1, n - half + 1);

    strncpy(first_half, argv[1], half);
    first_half[half] = '\0';
    strcpy(second_half, argv[1] + half);

    // printf("%s %s\n", first_half, second_half);

    pid_t child_p1 = fork();
    run_proccess(child_p1, first_half, argv, 1);

    pid_t child_p2 = fork();
    run_proccess(child_p2, second_half, argv, 2);

    int status1, status2;
    waitpid(child_p1, &status1, 0);
    waitpid(child_p2, &status2, 0);

    printf("%d %d %s %d\n", getpid(), child_p1, first_half, WEXITSTATUS(status1));
    printf("%d %d %s %d\n", getpid(), child_p2, second_half, WEXITSTATUS(status2));

    exit(WEXITSTATUS(status1) + WEXITSTATUS(status2));
}
