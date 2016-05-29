#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <limits.h>

using namespace std;

void assign_ranks(vector<string>, map<string, int>&);
void print_val(string[], int, map<string, int>);

int main() {
    int scenario;
    ifstream myfile("input.txt");
    myfile >> scenario;
    int curr_scenario = 1;
    while (curr_scenario <= scenario) {
        int p, n;
        myfile >> p;
        myfile >> n;
        string line;
        myfile.ignore(100, '\n');
        map<string, int> author_map;
        author_map["Erdos, P."] = 0;
        
        while (p > 0) {
            getline(myfile, line);
            int colon_index = line.find(".:");
            int start_index = 0;
            int end_index = 0;
            vector<string> author_list;
            while (end_index < colon_index) {
                end_index = line.find(".,", start_index)+1;
                if (end_index == 0) {
                    end_index = colon_index+1;
                }
                string author = line.substr(start_index, (end_index-start_index));
                start_index = end_index+2;
                author_list.push_back(author);
            }
            p--;
            assign_ranks(author_list, author_map);
        }
        string array[n];
        int i = 0;
        while (i < n) {
            getline(myfile, array[i]);
            i++;
        }
        cout << "Scenario " << curr_scenario << endl;
        print_val(array, n, author_map);
        curr_scenario++;
    }
    return 0;
}

void assign_ranks(vector<string> author_list, map<string, int> &author_map) {
    int min_rank = INT_MAX;
    for (vector<string>::iterator it = author_list.begin(); it != author_list.end(); it++) {
        if (author_map.find(*it) != author_map.end()) {
            int rank = author_map[*it];
            if (rank < min_rank) {
                min_rank = rank;
            }
        }
    }
    if (min_rank == INT_MAX) {
        min_rank = -2;
    }
    for (vector<string>::iterator it = author_list.begin(); it != author_list.end(); it++) {
        if (author_map.find(*it) != author_map.end()) {
            if(author_map[*it] > (min_rank+1)) {
                author_map[*it] = min_rank + 1;
            }
        } else {
            author_map[*it] = min_rank + 1;
        }
    }
}

void print_val(string array[], int n, map<string, int> author_map) {
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
        if (author_map[array[i]] == 0) {
            if (array[i] == "Erdos, P.") {
                cout << 0;
            } else {
                cout << "infinity";
            }
        } else if (author_map[array[i]] == -1) {
            cout << "infinity";
        } else {
            cout << author_map[array[i]];
        }
        cout << endl;
    }
}
