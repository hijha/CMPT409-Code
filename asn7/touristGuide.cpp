#include <algorithm>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

int matrix[105][105];
int visited[105];
string cities[105];
vector<string> locations;


void depthFirstSearch(int, int, int);
void findPoints(int);

int main() {
    int no_of_cities;
    int num = 1;
    int first = true;
    while ((cin >> no_of_cities)) {
        if (no_of_cities == 0) {
            break;
        }
        if (!first) {
            cout << endl;
        }
        first = false;
        
        memset(matrix, 0, sizeof(matrix));
        locations.clear();
        
        for (int i = 0; i < 105; i++) {
            cities[i].clear();
        }

        for (int i = 1; i <= no_of_cities; i++) {
            cin >> cities[i];
        }
        int connections;
        cin >> connections;
        while (connections > 0) {
            string first, second;
            cin >> first >> second;
            int x = -1, y = -1;
            for (int i = 1; i <= no_of_cities; i++) {
                if (first == cities[i]) {
                    x = i;
                }
                if (second == cities[i]) {
                    y = i;
                }
            }
            matrix[x][y]++;
            matrix[y][x]++;
            connections--;
        }
        
        cout << "City map #" << num <<": ";
        num++;
        findPoints(no_of_cities+1);
    }
}

void findPoints(int size) {    
    for (int i = 1; i < size; i++) {
        int start = i+1;
        if (i == size-1) {
            start = 1;
        }
        memset(visited, 0, sizeof(visited));
        bool connected = true;
        visited[i] = 1;
        depthFirstSearch(start, size, i);
        for (int j = 1; j < size; j++) {
            if (!visited[j]) {
                connected = false;
                break;            
            }
        }
        if (!connected) {
            locations.push_back(cities[i]);
        }
    }
    cout << locations.size() << " camera(s) found" << endl;
    sort(locations.begin(), locations.end());
    for (int i = 0; i < locations.size(); i++) {
        cout << locations[i] << endl;
    }
}

void depthFirstSearch(int start, int size, int index) {
    visited[start] = 1;
    for (int i = 1; i < size; i++) {
        if (i != index && matrix[start][i] && !visited[i]) {
            depthFirstSearch(i, size, index);
        }
    }
}
