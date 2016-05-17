#include <stdio.h>

using namespace std;

int findCycleLength(long number) {
    int cycleLength = 0;
    while (number != 1) {
        if (number % 2 == 0) {
            number /= 2;
            cycleLength++;
        } else {
            number = 3 * number + 1;
            cycleLength++;
        }
    }
    return cycleLength+1;
}

int main() {
    long first, second;
    while ((scanf("%ld %ld", &first, &second)) ==2) {
        bool swapped = false;
        long max = -1;
        if (first > second) {
            long temp = first;
            first = second;
            second = temp;
            swapped = true;
        }
        for (int i = first; i <= second; i++) {
            int cycleLength = findCycleLength(i);
            if (cycleLength > max) {
                max = cycleLength;
            }
        }
        if (swapped) {
            printf("%ld %ld %ld\n", second, first, max);
        } else {
            printf("%ld %ld %ld\n", first, second, max);
        }
    }
    return 0;
}
