#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void print_error_and_exit(char *message);
void if_args_len_is_one_exit_with_arg(char *argv[]);
void validate_args_are_decimal(char *argv[]);
void validate_args_count(int argc, char *argv[]);
void validate_args_properties(int argc, char *argv[]);
void createChildProcess(char *arg);

int main(int argc, char *argv[])
{

    validate_args_properties(argc, argv);

    int half = strlen(argv[1]) / 2;

    char firstHalf[half + 1];
    char secondHalf[half + strlen(argv[1]) % 2 + 1];

    strncpy(firstHalf, argv[1], half);
    firstHalf[half] = '\0';
    strcpy(secondHalf, argv[1] + half);

    createChildProcess(firstHalf);
    createChildProcess(secondHalf);

    return 0;
}

void createChildProcess(char *arg)
{
    PROCESS_INFORMATION pi;
    STARTUPINFO si;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    // Tworzenie nowego procesu
    if (!CreateProcess(NULL, arg, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        print_error_and_exit("Błąd: Nie udało się utworzyć procesu potomnego.\n");
    }

    // Oczekiwanie na zakończenie procesu potomnego
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Pobranie kodu zakończenia procesu potomnego
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // Wypisanie informacji o procesie potomnym
    printf("%d %d %s %d\n", GetCurrentProcessId(), pi.dwProcessId, arg, exitCode);

    // Zamknięcie uchwytów do procesu potomnego
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

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
