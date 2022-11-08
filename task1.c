// завдання просто на вивід того, що робити та чи інша команда
// компіляція: `gcc task1.c -o mane
// використання: ./mane -acd або ./mane -a -c -d
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
void help();
int main(int argc, char *argv[]) {

    int opt;
    // якщо без аргументів (перший аргумент - `./a.out`)
    if (argc == 1) {
        help();
        return 0;
    }

    // в getopt забираємо аргументи і записуємо в opt, поки не буде прочитаний кожен
    while ((opt = getopt(argc, argv, "abcdefg")) != -1) {
        switch (opt) {
            case 'a':
                printf("Current process ID: %d\n", getpid());
                break;
            case 'b':
                printf("Current process PID: %d\n", getppid());
                break;
            case 'c':
                printf("ID of group, which executes process: %d\n", getpgrp());
                break;
            case 'd':
                printf("Current process UID: %d\n", (int) getuid());
                break;
            case 'e':
                printf("Current process eUID: %d\n", (int) geteuid());
                break;
            case 'f':
                printf("Current process GID: %d\n", (int) getgid());
                break;
            case 'g':
                printf("eGID: %d\n", getegid());
                break;
        }
    }
}
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>

#include <sys/types.h>
extern char *optarg;

extern int optind, opterr, optopt;
void help() {
    printf("NAME\n"
           "       main - a program that outputs in a standard flow of process output\n\n"
           "SYNOPSIS\n"
           "       ./mane [value]...\n\n"
           "DESCRIPTION\n"
           "       -a prints current process ID\n\n"
           "       -b prints current process PID\n\n"
           "       -c prints ID of group, which executes process\n\n"
           "       -d prints current process UID\n\n"
           "       -e prints current process eUID\n\n"
           "       -f prints current process GID\n\n"
           "       -g prints eGID\n\n"
    );

}
