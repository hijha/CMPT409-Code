#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Time {
    int day, hour, min;
    int distance;
    bool enter;
};

void find_cost(map<string, vector<Time> >, int[]);

int main() {
    int testcases;
    cin >> testcases;
    cin.ignore(100, '\n');
    cin.ignore(100, '\n');
    string input_line;

    while (testcases-- > 0) {
        int toll[24];
        int i = 0;
        getline(cin, input_line);
        stringstream ss(input_line);
        for (int i=0; i<24; i++) {
            ss >> toll[i];
        }

        map <string, vector<Time> > license_map;
        while(true) {
            getline(cin, input_line);
            if (input_line.length() == 0) {
                break;
            }
            
            ss.str("");
            ss.clear();
            ss << input_line;
            
            string license;
            int month;
            Time time;
            string status;
            int distance;
            char sep;
            ss >> license >> month >> sep >> time.day >> sep >> time.hour >> sep >> time.min >> status >> time.distance;
            time.enter = (status == "enter") ? true : false;
            license_map[license].push_back(time);
        }
        find_cost(license_map, toll);
        if (testcases != 0) {
            cout << endl;
        }
    }
    
    return 0;
}

bool val_compare(Time time1, Time time2) {
    int time_val1 = time1.day*24*60 + time1.hour*60 + time1.min;
    int time_val2 = time2.day*24*60 + time2.hour*60 + time2.min;
    return time_val1 < time_val2;
}

void find_cost(map<string, vector<Time> > license_map, int toll[]) {
    for (map<string, vector<Time> > :: iterator it = license_map.begin(); it != license_map.end(); it++) {
        sort(it->second.begin(), it->second.end(), val_compare);
        if (it->second.size() != 1) {
            double total_cost = 0;
            for (int i = 0; i < it->second.size() - 1; i++) {
                if (it->second[i].enter == true && it->second[i+1].enter == false) {
                    int distance = abs(it->second[i].distance - it->second[i+1].distance);
                    total_cost += ((toll[it->second[i].hour])*(double)distance)/100;
                    total_cost += 1;
                }
            }
            if (total_cost != 0) {
                cout << it->first << " $" << setprecision(2) << fixed << total_cost + 2 << endl;
            }
        }
    }
}
