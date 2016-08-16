#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <sstream>

using namespace std;

void sort(int[], int, int);
int find_partition(int[], int, int);
void find_bridge_combinations(vector<int>);
bool pick_first_over_second(int, int, int, int);

int main() {
    int testcases;
    cin >> testcases;
    cin.ignore(100, '\n');
    while (testcases > 0) {
        vector<int> list;
        int size;
        cin >> size;
        int array[size];
        for (int i = 0; i < size; i++) {
            cin >> array[i];
        }
        sort (array, 0, size-1);
        for (int i = 0; i < size; i++) {
            list.push_back(array[i]);
        }
        find_bridge_combinations(list);
        testcases--;
        if (testcases != 0) {
            cout << endl;
        }
    }
    return 0;
}

void sort(int array[], int start, int end) {
    int partition = find_partition(array, start, end);
    if (start < partition-1) {
        sort(array, start, partition-1);
    }
    if (partition < end) {
        sort(array, partition, end);
    }
    
}

int find_partition(int array[], int start, int end) {
    int i = start;
    int j = end;

    int partition = (i+j)/2;
    int pivot = array[partition];
    
    while (i <= j) {
        while (array[i] < pivot) {
            i++;
        }
        while (array[j] > pivot) {
            j--;
        }
        if (i <= j) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}
void find_bridge_combinations(vector<int> list) {
    int total_time = 0;
    string result;
    ostringstream oss;
    int size = list.size();
    /*
        first = AD, A, AC, A
        sec = AB, A, CD, B
    */
    while (list.size() >= 4) {
        if (pick_first_over_second(list[0], list[1], list[size-2], list[size-1])) {
            oss << list[0] << " " << list[size-1] << "\n";
            oss << list[0] << "\n";
            oss << list[0] << " " << list[size-2] << "\n";
            oss << list[0] << "\n";
            total_time += (2*list[0] + list[size-2] + list[size-1]);
        } else {
            oss << list[0] << " " << list[1] << "\n";
            oss << list[0] << "\n";
            oss << list[size-2] << " " << list[size-1] << "\n";
            oss << list[1] << "\n";
            total_time += (list[0] + 2*list[1] + list[size-1]);
        }
        list.pop_back();
        list.pop_back();
        size = list.size();
    }
    if (list.size() == 1) {
        total_time += list[0];
        oss << list[0] << "\n";
    } else if (list.size() == 3) {
        total_time += (list[1] + list[0] + list[2]);
        oss << list[0] << " " << list[2] << "\n";
        oss << list[0] << "\n";
        oss << list[0] << " " << list[1] << "\n";
    } else {
        total_time += list[1];
        oss << list[0] << " " << list[1] << "\n";
    }
    
    cout << total_time << endl;
    cout << oss.str();
}

bool pick_first_over_second(int first, int sec, int third, int fourth) {
    int first_val = (2*first + third + fourth);
    int sec_val = (first + 2*sec + fourth);
    return first_val < sec_val;
}
