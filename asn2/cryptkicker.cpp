#include<algorithm>
#include<fstream>
#include<iostream>
#include<map>
#include<stdio.h>
#include<vector>

using namespace std;

bool decrypt(map<int, vector<string> >, vector<string>, map<char, char>&);

int main() {

    ifstream myfile("input.txt");
    int dictionary_size;
    myfile >> dictionary_size;
    string dictionary[dictionary_size];
    int i = 0;
    while (i < dictionary_size) {
        myfile >> dictionary[i];
        i++;
    }
    
    map<int, vector<string> > word_length_map;
    for (i = 0; i < dictionary_size; i++) {
        int length = dictionary[i].size();
        if (word_length_map.find(length) != word_length_map.end()) {
            vector<string> word_vector = word_length_map[length];
            word_vector.push_back(dictionary[i]);
            word_length_map[length] = word_vector;
        } else {
            vector<string> word_vector;
            word_vector.push_back(dictionary[i]);
            word_length_map[length]  = word_vector;
        }
    }

    myfile.ignore(100, '\n');
    string line;
    getline(myfile, line);
    vector<string> crypt;
    while (true) {
        int index = line.find(" ");
        if (index == -1) {
            crypt.push_back(line);
            break;
        }
        string word = line.substr(0, index);
        crypt.push_back(word);
        line = line.substr(index+1);
    }
    
    map <char, char> code;
    bool result = decrypt(word_length_map, crypt, code);
    if (result) {
        for (map<char, char>::iterator it = code.begin(); it != code.end(); it++) {
            //cout << it->first << " " << it->second << endl;
        }
    } else {
        cout << "False" << endl;
    }
    return 0;
}

bool decrypt (map<int, vector<string> > word_length_map, vector<string> crypt, map<char, char> &code) {
    map<string, vector<string> > possible_decrypts;
    for (int i = 0; i < crypt.size(); i++) {
        int length = crypt[i].length();
        if (word_length_map.find(length) == word_length_map.end()) {
            return false;
        } else {
            if (word_length_map[length].size() == 1 && possible_decrypts.find(crypt[i]) == possible_decrypts.end()) {
                string word_found = word_length_map[length].at(0);
                possible_decrypts[crypt[i]] = word_length_map[length];
                for (int j = 0; j < length; j++) {
                    if (code.find(crypt[i].at(j)) != code.end()) {
                        if (word_found.at(j) != code[crypt[i].at(j)]) {
                            return false;
                        }
                    } else {
                        code[crypt[i].at(j)] = word_found.at(j);
                    }
                }
            } else {
                possible_decrypts[crypt[i]] = word_length_map[length];
            }
        }
    }
    return true;
}
