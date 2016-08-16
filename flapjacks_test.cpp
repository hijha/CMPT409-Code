#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

void sort(int[], int, int);
int find_partition(int[], int, int);
int findElemInArray(int[], int, int);
bool reverseArray(int[], int);
void print(int[], int);

int main() {
    ifstream myfile("input.txt");
    string line;
    while(getline(myfile, line)) {
        string result = "";
        istringstream iss(line);
        vector<int> list;
        while(!iss.eof()) {
            string sub;
            iss >> sub;
            int val = atoi(sub.c_str());
            list.push_back(val);
            cout << val << " ";
        }
        cout << endl;
        iss.clear();

        int size = list.size();
        int array[size];
        int sortedArray[size];
        
        for (int i = 0; i < size; i++) {
            array[i] = list[i];
            sortedArray[i] = list[i];
        }
        
        sort(sortedArray, 0, size-1);
        int expectedPosition = size -1;
        int index;
        for (int i = size-1; i >= 0; i--) {
            int elem = sortedArray[i];
            index = findElemInArray(array, elem, size-1);
            if (index != expectedPosition) {
                if(reverseArray(array, index)) {
                    ostringstream oss;
                    oss << (size-index);
                    result += (oss.str() + " ");
                }
                
                if(reverseArray(array, expectedPosition)) {
                    ostringstream oss;
                    oss << (size-expectedPosition);
                    result += (oss.str() + " ");
                }
            }
            expectedPosition--;
            print(array, size);
        }
        cout << result <<"0\n";
    }
    return 0;
}

void print(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

bool reverseArray(int array[], int endIndex) {
    bool reversed = false;
    for (int i = 0, j = endIndex; i < j; i++, j--) {
        reversed = true;
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
    return reversed;
}

int findElemInArray(int array[], int elem, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == elem) {
            return i;
        }
    }
}

void sort(int sortedArray[], int start, int end) {
    int partition = find_partition(sortedArray, start, end);
    if (start < partition-1) {
        sort(sortedArray, start, partition-1);
    }
    if (partition < end) {
        sort(sortedArray, partition, end);
    }
    
}

int find_partition(int sortedArray[], int start, int end) {
    int i = start;
    int j = end;

    int partition = (i+j)/2;
    int pivot = sortedArray[partition];
    
    while (i <= j) {
        while (sortedArray[i] < pivot) {
            i++;
        }
        while (sortedArray[j] > pivot) {
            j--;
        }
        if (i <= j) {
            int temp = sortedArray[i];
            sortedArray[i] = sortedArray[j];
            sortedArray[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}
