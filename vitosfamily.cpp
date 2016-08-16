#include<iostream>
#include<stdio.h>
#include<cmath>
#include<fstream>
#include<climits>

using namespace std;

void sort(int[], int, int);
int find_partition(int[], int, int);

int main() {
    int testcases;
    cin >> testcases;
    while (testcases > 0) {
        int no_of_rels;
        cin >> no_of_rels;
        int streets[no_of_rels];
        int i =0;
        while (no_of_rels > 0) {
            cin >> streets[i];
            no_of_rels--;
            i++;
        }
        int size = i;
        sort(streets, 0, size-1);
        int median;
        if (size % 2 == 0) {
            int mid = size/2;
            median = (streets[mid] + streets[mid-1])/2;
        } else {
            median = streets[size/2];
        }
        for (int i = 0; i < size; i++) {
//            cout << streets[i] << endl;
        }
        int totalDistance = 0;
        for (int i = 0; i < size; i++) {
            totalDistance += abs(median - streets[i]);
        }
        cout << totalDistance << endl;
        testcases--;
    }
    return 0;
}

void sort(int streets[], int start, int end) {
    int partition = find_partition(streets, start, end);
    if (start < partition-1) {
        sort(streets, start, partition-1);
    }
    if (partition < end) {
        sort(streets, partition, end);
    }
    
}

int find_partition(int streets[], int start, int end) {
    int i = start;
    int j = end;

    int partition = (i+j)/2;
    int pivot = streets[partition];
    
    while (i <= j) {
        while (streets[i] < pivot) {
            i++;
        }
        while (streets[j] > pivot) {
            j--;
        }
        if (i <= j) {
            int temp = streets[i];
            streets[i] = streets[j];
            streets[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}
