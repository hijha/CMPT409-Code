#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    int array[3000];
    int diffArray[2999]; 
    int size;
    char input;
    while (cin >> size) {
        for (int i = 0; i < 3000; i++) {
            array[i] = 0;
        }
        for (int i = 0; i < 2999; i++) {
            diffArray[i] = false;
        }

        int val;
        int i =0;
        while (cin >> val) {
            array[i] = val;
            i++;
            if (i == size) {
                break;
            }
        }

        for (i = 0; i < size-1; i++) {
            int diff = abs(array[i] - array[i+1]);
            if (diff >= size || diff < 1 || diffArray[diff]) {
                cout << "Not jolly" << endl ;
                break;
            }
            diffArray[diff] = true;
        }
        if (i == size-1)
            cout << "Jolly" << endl;
    }
    return 0;
}
