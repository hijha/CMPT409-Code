#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

bool check_sorted(vector<int>);
int findLargestPos(vector<int>, int);
void print(vector<int>);

int main() {
//    ifstream myfile("input.txt");
    string line;
    while(getline(cin, line)) {
        istringstream iss(line);
        vector<int> list;
        while(!iss.eof()) {
            string sub;
            iss >> sub;
            int val = atoi(sub.c_str());
            list.push_back(val);
        }
        for (int i = 0; i < list.size(); i++) {
            cout << list[i];
            if (i != list.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
        iss.clear();
        
        int expectedPos = list.size()-1;
        int size = list.size();
        while (!check_sorted(list)) {
            int largest_pos = findLargestPos(list, expectedPos +1);
            if (largest_pos == 0) {
                cout << (size - expectedPos) <<  " ";
                reverse(list.begin(), list.begin() + expectedPos+1);
            } else if (expectedPos != largest_pos) {
                reverse(list.begin(), list.begin() + largest_pos+1);
                cout << (size - largest_pos) <<  " ";
                reverse(list.begin(), list.begin() + expectedPos+1);
                cout << (size - expectedPos) <<  " ";
            }
            expectedPos--;
        }
        cout << "0\n";
    }
    return 0;
}

void print(vector<int> list) {
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;
}

bool check_sorted(vector<int> list) {
    for (int i = 1; i < list.size(); i++) {
        if (list[i] < list[i-1]) {
            return false;
        }
    }
    return true;
}

int findLargestPos(vector<int> list, int limit) {
    int max = INT_MIN;
    int index = -1;
    for (int i = 0; i < limit; i++) {
        if (list[i] > max) {
            max = list[i];
            index = i;
        }
    }
    return index;
}
