#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void hr();
int main (void) {
    int status;
    int pid;

    if ((pid = fork()) == 0) {
        // виконуємо команду ls в консолі
        execlp("ls", "ls", NULL);
        // якщо буде помилка, то воно напише
        fprintf (stderr, "Exec error\n");
        // друкумо процес айді
        printf("Process ID: %d", pid);
        exit(0);
    }
    hr();
    // виводимо процеси
    system("ps");
    hr();
    // засианаємо на 40 секунд, бо тоді не буде працювати, ггг. Можна менше
    sleep(40);

    // очікуємо результат функції
    wait(&status);
    // WIF... спеціальні макроси
    /*
     * 1. WIFEXITED(status): дитина вийшла нормально |||| child exited normally
        • WEXITSTATUS(status): код поверенення, коли дитина вийшла |||| return code when child exits
    2. WIFSIGNALED(status): дитина вийшла, бо сигнал не спіймано |||| child exited because a signal was not caught
        • WTERMSIG(status): отримує номер сигналу, що закінчив |||| gives the number of the terminating signal
        3. WIFSTOPPED(status): дитина зупинена |||| child is stopped
        • WSTOPSIG(status): отримує число стоп-сигналу |||| gives the number of the stop signal
     */
    if (WIFEXITED (status)) {
        printf ("Code=%d\n", WEXITSTATUS(status));
    }
    hr();
    // виводимо процеси ще раз, щоби упевнитися, що все ок
    system("ps");
    hr();
    return 0;
}

// некрасиво виглядає повторення в коді, то вирішено перенести в окрему функцію
void hr() {
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}