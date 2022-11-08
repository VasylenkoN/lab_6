#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    // зберігаємо айді батьківскього процесу
    // взагалі це можна було не робити, але тут багато процесів треба зробити, проте йой, най буде
    int parent_process_id = getpid();

    // якщо кількість аргументів = 1
    if (argc == 1) {
        printf("loh");
        return 0;
    }

    // виводимо айді поточного процесу
    printf("Current process PID/ID: %d\n", getpid());
    // з аргумента беремо скільки дітей ми хочемо, робимо конвертації з atoi із стрінга в число
    int num_of_childs = atoi(argv[1]);
    // проста перевірка на кількість
    if (num_of_childs <= 0) {
        printf("Number must > 0");
        return 1;
    }
    // масив, де будуть зберігатися айдішники дітей
    int arrPids[num_of_childs];
    // запускаємо цикл по діятм
    for (int i = 0; i < num_of_childs; i++) {
        // отримаємо процес айді
        int pid = fork();
        // якщо це дочірній процес
        if (pid > 0) {
            // то зберігаємо айді цього процеса в масиві
            arrPids[i] = pid;
        } else if (pid == 0) {
            // якщо батьківський процес
            printf("Current process PID/ID: %d %d\n", getppid(), getpid());
            int hehe = 0;
            while (1) {
                hehe++;
            }
        }
    }
    // просто виводимо айдішки всіх процесів
    printf("\nArray:\t");
    for (int i = 0; i < num_of_childs; i++) {
        printf("%d, ", arrPids[i]);
    }
    // якщо поточний процес батьківський, то...
    if (parent_process_id == getpid()) {

        // ці полоски просто для розділення
        
        printf("\n===============================================\n");
        // виводить усі процеси
        system("ps");
        printf("\n===============================================\n");
        printf("\n");
        // тут відбувається вбивство дітей ахпха
        for (int i = 0; i < num_of_childs; ++i) {
            // вбиваємо процес за допомогою сигналу SIGKILL та його айді
            kill(arrPids[i], SIGKILL);
            printf("Child %d has been killed!\n", arrPids[i]);
        }

        // виводимо усі процеси, defunct =  убитий процес
        printf("\n===============================================\n");
        system("ps");
        printf("\n===============================================\n");

    }
    return 0;
}

