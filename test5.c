#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>


// потрібно скомпілювати test.c в `test`
// `gcc test.c -o test`
int main (int argc, char *argv[]) {
    // pid_t зберігаємо процес ідентифікатор
    // форк створює дочірній процес
    pid_t pid = fork();

    // якщо менше нуля, то якась помилка
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    // якщо дочірній процес
    if (pid == 0)
    {
        // просто зберігаємо десь яку програму нам слід запустити
        argv[0] = "./test";
        // execute file. виконуємо файл ./test і передаємо аргументи
        // по іншому можна було зробити так execv("./test", "./test", NULL);
        execv(argv[0], argv);
        // якщо буде помилка при запуску або що, то воно виведе
        perror("execv");
        return 1;
    }

    int status;
    pid_t wait_result;
    // чекаємо поки не виконається test.c
    // потім значення, яке повернула програма, повертається в status, а в wait_result повертається процес айді
    while ((wait_result = wait(&status)) != -1) {
        printf("Process %lu returned result: %d\n", (unsigned long) wait_result, status);
    }
    return 0;
}