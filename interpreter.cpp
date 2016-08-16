#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <iomanip>

using namespace std;

int ram[1000];
int regs[10];

int operations(int inst) {
    int c = inst/100;
    int f = (inst/10)%10;
    int s = inst % 10;
    switch(c) {
        case 1 :
            return -1;
        case 2 :
            regs[f] = s;
            return 1;
        case 3 : 
            regs[f] = (regs[f] + s) % 1000;
            return 1;
        case 4 :
            regs[f] = (regs[f] * s) % 1000;
            return 1;
        case 5 :
            regs[f] = regs[s];
            return 1;
        case 6 :
            regs[f] = (regs[f] + regs[s]) % 1000;
            return 1;
        case 7 :
            regs[f] = (regs[f] * regs[s]) % 1000;
            return 1;
        case 8 :
            regs[f] = ram[regs[s]];
            return 1;
        case 9 :
            ram[regs[s]] = regs[f];
            return 1;
        case 0 :
            if (regs[s] != 0) {
                return regs[f];
            } else {
                return 1;
            }
    }
}

void initializeArrays() {
    for (int i =0; i < 10; i++) {
        regs[i] = 0;
    }
    for (int i =0; i < 1000; i++) {
        ram[i]= 0;
    }

}

int main() {
//    if (myfile.is_open()) {
    int testcases;
    cin >> testcases;
//    myfile >> testcases;
    string input;
    cin.ignore(100, '\n');
    cin.ignore(100, '\n');
//    myfile.ignore(100, '\n');
//    myfile.ignore(100, '\n');
    while (testcases != 0) {
        initializeArrays();
        int i = 0;
        int count = 0;
        while (true) {
            getline(cin, input);
//            getline(myfile, input);
            if (input.length() == 0) {
                break;
            }
            int inst = (input.at(0)-'0')*100 + (input.at(1)-'0')*10 + (input.at(2)-'0');
            ram[i] = inst;
            i++;
        }
        int start = 0;
        while (true) {
            int val = operations(ram[start]);
            count++;
            if (val == -1) {
                break;
            } else if (val == 1) {
                start++;
            } else {
                start = val;
            }
        }
        cout << count << endl;        
        testcases--;
        if (testcases !=0) {
            cout << endl;
        }
    }
}
