#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
using namespace std;

class Bead {
    int start;
    int end;
    
    public:
    Bead(int s, int e) : start(s), end(e){}
    
    int getStart() { return start;}
    
    int getEnd() { return end;}
};

int matrix[55][55];
int degree[55];
vector<Bead> paths;

bool checkDegree() {
    for (int i =0; i < 55; i++) {
        if (degree[i] % 2 == 1) {
            return false;
        }
    }
    return true;
}

void createPath(int start, int N) {
    for (int i = 1; i <= N; i++) {
        if (matrix[start][i] != 0) {
            matrix[start][i]--;
            matrix[i][start]--;
            createPath(i, N);
            paths.push_back(Bead(start, i));
        }
    }
}

int main() {
    int testcase;
    cin >> testcase;
    int caseNo = 1;
    while (testcase > 0) {
        int edges;
        cin >> edges;
        
        int startingPoint = -1;
        memset(matrix, 0, sizeof(matrix));
        memset(degree, 0, sizeof(degree));
        paths.clear();
        
        int index = edges;
        while (index > 0) {
            int start, end;
            cin >> start >> end;
            matrix[start][end]++;
            matrix[end][start]++;
            degree[start]++;
            degree[end]++;

            startingPoint = max(startingPoint, max(start, end));
            index--;
        }

        bool deg = checkDegree();

        cout << "Case #" << caseNo << endl;
        if (!deg) {
            cout << "some beads may be lost" << endl;
        } else {
            createPath(startingPoint, startingPoint);
            if (paths.size() != edges) {
                cout << "some beads may be lost" << endl;
            } else if (paths[paths.size()-1].getStart() != paths[0].getEnd()) {
                cout << "some beads may be lost" << endl;
            } else {
                for (int i = paths.size()-1; i >= 0; i--) {
                    cout << paths[i].getStart() << " " << paths[i].getEnd() << endl;
                }
            }
        }
        testcase--;
        caseNo++;
        if (testcase != 0) {
            cout << endl;
        }
    }
}
