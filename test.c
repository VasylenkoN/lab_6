
// майже нескінченний цикл
int main() {
    int a = 0;
    while (a < 999999) {
        a++;
    }

    // цікавий факт, воно чомусь повертає не 3, а 3 * 256. Так само і з іншими числами, тож при поверненні можна розділити на 3 :|
    return 3;
}