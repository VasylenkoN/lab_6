#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define SEED time(NULL)
// метод Монте Карло
// Детальініше (там класна гіфка є):
// https://uk.wikipedia.org/wiki/%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%9C%D0%BE%D0%BD%D1%82%D0%B5-%D0%9A%D0%B0%D1%80%D0%BB%D0%BE
int main(int argc, char *argv[]) {
    int i, count, n;
    double x,y,s,pi;

    srand( SEED );
    // в інт перетворюємо аргумент
    n = atoi(argv[1]);

    count = 0;

    // крч, основний прикол алгоритму полягає в тому, щоби знайти число пі
    // через площу випадкових прямокутників
    for(i = 0; i < n; ++i) {
        // рандомні точки (RAND_MAX = at least 32767)
        // rand() повертає інт в діапазоні [0...RAND_MAX].
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        // площа прямокутника
        s = x * x + y * y;
        // якщо площа менше одного, то попали в коло
        if( s <= 1 ) count++;
    }

    // математика :/
    pi = (double) count / n * 4;

    // приблизне пі
    printf("Approximate PI = %g", pi);
    // передаємо кількість потраплянь
    return count;
}