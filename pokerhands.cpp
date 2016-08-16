#include<iostream>
#include<string>
#include<stdio.h>
#include<fstream>
#include<map>

using namespace std;

int get_card_value(string);
void get_hand_rank(int[], int[]);
int check_card_val(int[], int[]);
bool check_straight(int[]);
bool check_flush(int[]);
void find_highest_card(int[]);

int main() {
    string line;
    while(getline(cin, line)) {
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
        get_hand_rank(black, white);
    }
    
    return 0;
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

void get_hand_rank(int black[], int white[]) {
    int rank = 0;
    int high_cards_black[5];
    int high_cards_white[5];
    for (int i = 0; i < 5; i++) {
        high_cards_black[i] = -1;
        high_cards_white[i] = -1;
    }
    int black_rank = check_card_val(black, high_cards_black);
    int white_rank = check_card_val(white, high_cards_white);
    
    bool black_flush = check_flush(black);
    bool black_straight = check_straight(black);
    bool white_flush = check_flush(white);
    bool white_straight = check_straight(white);
    
    if (black_flush) {
        if (black_straight) {
            black_rank = 8;
        } else {
            if (black_rank < 5) {
                black_rank = 5;
            }
        }
    } else if (black_straight && black_rank < 4) {
        black_rank = 4;
    }

    if (white_flush) {
        if (white_straight) {
            white_rank = 8;
        } else {
            if (white_rank < 5) {
                white_rank = 5;
            }
        }
    } else if (white_straight && white_rank < 4) {
        white_rank = 4;
    }
    if (black_rank > white_rank) {            
        cout << "Black wins." << endl;
    } else if (white_rank > black_rank) {
        cout << "White wins." << endl;
    } else {
        if (black_rank == 4 || black_rank == 5 || black_rank ==8) {
            find_highest_card(high_cards_black);
            find_highest_card(high_cards_white);
        }
        bool winner = false;        
        for (int i = 0; i < 5; i++) {
            if (high_cards_black[i] > high_cards_white[i]) {
                cout << "Black wins." << endl;
                winner = true;
                break;
            } else if (high_cards_white[i] > high_cards_black[i]) {
                cout << "White wins." << endl;
                winner = true;
                break;
            }
        }
        if (!winner) {
            cout << "Tie." << endl;
        }
    }
}

void get_high_card(map<int, int> m, int high_card[]) {
    map<int,int>::iterator it = m.end();
    int i = 0;
    while (i != 5) {
        it--;
        high_card[i] = it->first;
        i++;
    }
}

int check_card_val(int array[], int high_card[]) {
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
        } else if (size == 5) {
            get_high_card(m, high_card);
            break;
        }
        if (it == m.begin()) {
            break;
        }
    }
    return rank;
}

bool check_straight(int array[]) {
    for (int i = 0; i < 5; i++) {
        array[i] = array[i]%13;
    }
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i =0; i < 4; i++) {
            if (array[i] > array[i+1]) {
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                swapped = true;
            }
        }
    }
    for (int i =0; i < 4; i++) {
        if ((array[i+1] - array[i]) != 1) {
            return false;
        }
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

void find_highest_card(int array[]) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i =0; i < 4; i++) {
            if (array[i] < array[i+1]) {
                int temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                swapped = true;
            }
        }
    }
}
