#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#define SEED time(NULL)

// УВАГА: ОБОВ'ЯЗКОВО СКОМПІЛЮВАТИ task7_additional.c
// логіка програми: забираємо перший аргумент, створюємо дочірній процес і передаємо його в нову програму (яка запускається в дочірньому процесі)
// потім очікуємо
int main(int argc, char *argv[]) {
    // унікальна перевірка на кількість аргументів (с)
    if (argc == 1) {
        printf("\ndurachek");
        return 0;
    }

    // в інт перетворюємо агрумент
    int n = atoi(argv[1]);
    printf("Arg1: %d\n", n);
    // записуємо айді процесора
    pid_t pid = fork();
    // якась помилка при створенні суб процеса
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    // якщо дитина, то
    if (pid == 0) {
        // тобто сходе на ./task7_additional.hehe <вставити число>
        execlp("./task7_additional.hehe", "./task7_additional.hehe", argv[1], NULL);
        perror("execv");
    }

    int status;
    pid_t wait_result;
    // чекаємо 10 секунд
    sleep(10);

    // чекаємо поки буде сигнал завершення
    while ((wait_result = wait(&status)) != -1) {
        printf("\n\nProcess %lu returned result: %d\n", (unsigned long) wait_result, status / 256);
    }
    // ділимо на 256, бо так треба, йо ._., в іншому випадку можна WIFEXITED і WEXITSTATUS, щоби не ділити на 256.
    // Детальніше в джерелі
    // джерело: https://stackoverflow.com/questions/24130990/i-used-waitstatus-and-the-value-of-status-is-256-why
    int m = (int) status / 256;
    // скільки потрапило відсотків
    printf("\nm(%d)/n(%d): %.3f percents\n", m, n, ((float) m/n * 100));
    return 0;
}