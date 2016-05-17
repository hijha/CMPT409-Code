#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
    int row, column;
    int count = 1;
    cin >> row >> column;
    while (row != 0 || column != 0) {
        if (row > 0 && column > 0) {
            char array[row][column];
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    char c;
                    cin >> c;
                    array[i][j] = c;
                }
            }

            int result[row][column];
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    result[i][j] = 0;
                }
            }

            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    if (array[i][j] == '*') {
                        for (int r = i-1; r <= i+1; r++) {
                            for (int c = j-1; c <= j+1; c++) {
                                if (r != -1 && c != -1 && r != row && c != column)
                                    if (result[r][c] != -1)
                                        result[r][c]++;
                            }
                        }
                        result[i][j] = -1;
                    }
                }
            }
            cout << "Field #" << count << ":" << endl;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    if (result[i][j] == -1)
                        cout << '*';
                    else
                        cout << result[i][j];
                }
	        cout << '\n';
            }
            count++;
        }
        cin >> row >> column;
        if (row != 0 && column != 0) {
            cout << '\n';
        }

    }
}
