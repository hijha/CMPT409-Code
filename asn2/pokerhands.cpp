#include<iostream>
#include<string>
#include<stdio.h>
#include<fstream>
#include<map>
#include <stdint.h>

using namespace std;

int get_card_value(string);
int get_hand_rank(int[]);
//int check_pairs(int[]);
int check_pairs(int[], int[]);
int count_val(int[], int&);
bool check_straight(int[]);
bool check_flush(int[]);
string high_card(int[], int[], int);

int main() {
    ifstream myfile ("input.txt");
    string line;
    while(getline(myfile, line)) {
        int white[5];
        int black[5];
        int i = 0;
        int index = -1;
        int size = line.size();
        while (i < 10) {
            index = line.find(" ");
            string card = line.substr(0, index);
            int card_val = get_card_value(card);
            line = line.substr(index+1);
            if (i < 5) {
                black[i] = card_val;
            } else {
                white[i-5] = card_val;
            }
            i++;
        }
        int high_cards_black[5];
        int high_cards_white[5];
        for (int i = 0; i < 5; i++) {
            high_cards_black[i] = -1;
            high_cards_white[i] = -1;
        }
        int black_rank = check_pairs(black, high_cards_black);
        int white_rank = check_pairs(white, high_cards_white);
        cout << "black rank = " << black_rank << endl;
        cout << "white rank = " << white_rank << endl;
        for (int i = 0; i < 5; i++) {
            cout <<  high_cards_black[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 5; i++) {
            cout << high_cards_white[i] << " ";
        }
        cout << endl;
        if (black_rank > white_rank) {            
            cout << "Black Wins." << endl;
        } else if (white_rank > black_rank) {
            cout << "White wins." << endl;
        } else {
            bool winner = false;
            for (int i = 0; i < 5; i++) {
                if (high_cards_black[i] > high_cards_white[i]) {
                    cout << "Black Wins." << endl;
                    winner = true;
                    break;
                } else if (high_cards_white[i] > high_cards_black[i]) {
                    cout << "White Wins." << endl;
                    winner = true;
                    break;
                }
            }
            if (!winner) {
                cout << "Tie." << endl;
            }
        }
    }
}

int get_card_value (string string_val) {
    int val;
    char card_val = string_val.at(0);
    if (card_val >= '2' && card_val <= '9') {
        val = (card_val - '0') - 2;
    } else {
        if (card_val == 'T') {
            val = 8;
        } else if (card_val == 'J') {
            val = 9;
        } else if (card_val == 'Q') {
            val = 10;
        } else if (card_val == 'K') {
            val = 11;
        } else if (card_val == 'A') {
            val = 12;
        }
    }

    char suit = string_val.at(1);
    int suit_val;
    if (suit == 'C') {
        suit_val = 0;
    } else if (suit == 'D') {
        suit_val = 1;
    } else if (suit == 'H') {
        suit_val = 2;
    } else {
        suit_val = 3;
    }
    int total_val = suit_val*13 + val;
    return total_val;
}

int get_hand_rank(int array[]) {
    int rank = 0;
    int high_value = 0;
    int val = count_val(array, high_value);
    cout << val << " " << high_value << endl;
/*    if (val > rank) {
        rank = val;
    }
    bool straight = check_straight(array);
    bool flush = check_flush(array);
    if (straight && flush) {
        rank = 8;
    } else if (flush && rank < 5) {
        rank = 5;
    } else if (straight && rank < 4){
        rank = 4;
    }
*/
    return rank;
}

int check_pairs(int array[], int high_card[]) {
    int rank = 0;
    map<int, int> m;
    for (int i = 0; i < 5; i++) {
        int card_val = array[i]%13;
        if (m.find(card_val) != m.end()) {
            int count = m[card_val];
            m[card_val] = count+1;
        } else {
            m[card_val] = 1;
        }
    }
    bool found_one_pair = false;
    bool found_three_of = false;
    map<int, int>::iterator it = m.end();
    int size = m.size();
    while (true) {
        it--;
        if (size == 2) {
            if (it->second == 4) {
                rank = 7;
                high_card[0] = it->first;
            } else if (it->second == 3) {
                rank = 6;
                high_card[0] = it->first;
                found_three_of = true;
            } else if (it->second == 1 || it->second == 2) {
                high_card[1] = it->first;
            }
        } else if (size == 3) {
            if (it->second == 3) {
                rank = 3;
                high_card[0] = it->first;
                found_three_of = true;
            } else if (it->second == 2) {
                if (found_one_pair) {
                    rank = 2;
                    if (high_card[1] != -1) {
                        high_card[2] = high_card[1];
                        high_card[1] = it->first;
                    } else {
                        high_card[1] = it->first;
                    }
                } else {
                    high_card[0] = it->first;
                    found_one_pair = true; 
                }
            } else if (it->second == 1) {
                if (high_card[1] == -1) {
                    high_card[1] = it->first;
                } else {
                    high_card[2] = it->first;
                }
            }
        } else if (size == 4) {
            rank = 1;
            if (it->second == 2) {
                high_card[0] = it->first;
            } else if (it->second == 1) {
                int i = 1;
                while (high_card[i] != -1) {
                    i++;
                }
                high_card[i] = it->first;
            } 
        }
        if (it == m.begin()) {
            break;
        }
    }
    return rank;
}

int count_val(int array[], int &high_card) {
    int rank = 0;
    map<int, int> m;
    bool one_pair = false;
    bool two_pair = false;
    bool three_of = false;
    for (int i = 0; i < 5; i++) {
        int card_value = array[i]%13;
//        cout << "teting .. " << card_value << endl;
        if (m.find(card_value) != m.end()) {
            if (m[card_value] == 1) {
                if (three_of) {
                    rank = 6;
                    return rank;
                } else if (one_pair) {
                    m[card_value] = 2;
                    two_pair = true;
                    if (card_value > high_card)
                        high_card = card_value;
//                    cout << "high card second pair" << high_card << endl;
                    rank = 2;
                } else {
                    m[card_value] = 2;
                    one_pair = true;
                    high_card = card_value;
//                    cout << "high card first pair " << high_card << endl;
                    rank = 1;
                }
            } else if (m[card_value] == 2) {
                if (two_pair) {
                    rank = 6;
                    high_card = card_value;
                    return rank;
                } else {
                    three_of = true;
                    rank = 3;
                    high_card = card_value;
                    m[card_value] = 3;
                }
            } else if (m[card_value] == 3) {
                m[card_value] = 4;
                high_card = card_value;
                rank = 7;
            }
        } else {
            m[card_value] = 1;
        }
    }
    return rank;
}

bool check_straight(int array[]) {
    int min = 100;
    int max = -1;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i =0; i < 4; i++) {
            if (array[i] < min)
                min = array[i];
            if (array[i] > max)
                max = array[i];
            if (array[i] > array[i+1]) {
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                swapped = true;
            }
        }
    }
    if (array[4] > max) 
        max = array[4];
    if (array[4] < min) 
        min = array[4];

    if ((min >= 0 && max < 13) || (min > 12 && max < 26) || (min > 25 && max < 39) || (min > 38 && max < 51)) {
        for (int i =0; i < 4; i++) {
            if ((array[i+1] - array[i]) != 1) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

bool check_flush(int array[]) {
    int min = 52;
    int max = -1;
    for (int i = 0; i < 5; i++) {
        if (array[i] < min)
            min = array[i];
        if (array[i] > max)
            max = array[i];
    }
    if ((min >= 0 && max < 13) || (min > 12 && max < 26) || (min > 25 && max < 39) || (min > 38 && max < 52)) {
        return true;
    } else {
        return false;
    }
}

string pair_tie_break(int black[], int white[]) {
    map<int, int> white_map;
    map<int, int> black_map;
    for (int i = 0; i < 5; i++) {
        int w_key = white[i]%13;
        int b_key = black[i]%13;
        if (white_map.find(w_key) != white_map.end()) {
            int val = white_map[w_key];
            white_map[w_key] = val+1;
        } else {
            white_map[w_key] = 1;
        }
        if (black_map.find(b_key) != black_map.end()) {
            int val = black_map[b_key];
            black_map[b_key] = val+1;
        } else {
            black_map[b_key] = 1;
        }
    }
}

string high_card(int black[], int white[], int size) {
    string result = "Tie.";
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i =0; i < size-1; i++) {
            if (black[i]%13 > black[i+1]%13) {
                int temp = black[i];
                black[i] = black[i+1];
                black[i+1] = temp;
                swapped = true;
            }
        }
    }

    swapped = true;
    while (swapped) {
        swapped = false;
        for (int i =0; i < size-1; i++) {
            if (white[i]%13 > white[i+1]%13) {
                int temp = white[i];
                white[i] = white[i+1];
                white[i+1] = temp;
                swapped = true;
            }
        }
    }

    for (int i = size-1; i >= 0; i--) {
        if (black[i]%13 > white[i]%13) {
            result = "Black Wins.";
            break;
        } else if (white[i]%13 > black[i]%13) {
            result = "White wins.";
            break;
        }
    }
    return result;
}
