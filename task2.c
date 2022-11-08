#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#define SEC 5

int main(void) {
    // тут будемо зберігати Process IDentificator
    pid_t pid;
    // робимо дочірній процес, fork повертає <0, коли помилка. Якщо = 0, то це батьківський процес. Якщо більше 0, то це айді на дочірній процес
    pid = fork();
    // лічильники
    int count_1 = 0, count_2 = 0;
    // обнулюємо час, бо так треба
    time(NULL);
    // записуємо у begin поточний час
    clock_t begin = clock();
    clock_t end;
    double time;

    // нескінченний цикл
    while (1) {
        // вимірюємо поточний час
        end = clock();
        // вираховує поточний час у секундах
        time = (double)(end - begin) / CLOCKS_PER_SEC;
        // якщо минуло понад 5 секунд, то зупиняємо цикл
        if (time >= SEC)
            break;
        // якщо батьківський процес, то рахуємо перший лічильник
        if (pid == 0) {
            count_1++;
            // якщо дочірній процес, то рахуємо другий лічильник
        } else if (pid > 0) {
            count_2++;
            // якщо pid < 0, то буде помилка через наприклад пам'ять, але зазвичай немає
        } else {
            printf("Error wiki fork, pad not created\n");
        }
    }
    // виводимо час, неперебачуваність полягає в тому, що по різному порахувало (лічильник 1 і 2 відповідно)
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n%d | %d | time = %d sec\n", count_1, count_2, (int)time);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    
    return 0;
}
