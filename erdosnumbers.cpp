#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <limits.h>
#include <queue>

using namespace std;

vector<string> get_author_list(string line);
void create_tree(vector<string>, map<string, vector<string> >&);
void assign_rank(map<string, int>&, map<string, vector<string> >);

int main() {
    map<string, vector<string> > author_tree;
    map<string, int> author_rank;
    int scenario;
    cin >> scenario;
    int curr_scenario = 1;
    while (curr_scenario <= scenario) {
        author_tree.clear();
        author_rank.clear();
        int p, n;
        cin >> p;
        cin >> n;
        string line;
        cin.ignore(100, '\n');
        while (p > 0) {
            getline(cin, line);
            vector<string> author_list = get_author_list(line);
            create_tree(author_list, author_tree);
            p--;
        }
        assign_rank(author_rank, author_tree);

        string array[n];
        int i = 0;
        while (i < n) {
            getline(cin, array[i]);
            i++;
        }
        cout << "Scenario " << curr_scenario << endl;
        for (int i = 0; i < n; i++) {
            cout << array[i] << " ";
            if (author_rank.find(array[i]) != author_rank.end()) {
                cout << author_rank[array[i]];
            } else {
                cout << "infinity";
            }
            cout << endl;
        }
        curr_scenario++;
    }
    return 0;
}

vector<string> get_author_list(string line) {
    vector<string> author_list;
    int colon_index = line.find(".:");
    int start_index = 0;
    int end_index = 0;
    while (end_index < colon_index) {
        end_index = line.find(".,", start_index)+1;
        if (end_index == 0) {
            end_index = colon_index+1;
        }
        string author = line.substr(start_index, (end_index-start_index));
        start_index = end_index+2;
        author_list.push_back(author);
    }
    return author_list;
}

void create_tree(vector<string> author_list, map<string, vector<string> > &author_tree) {
    for (vector<string>::iterator i = author_list.begin(); i != author_list.end(); i++) {
        for (vector<string>::iterator j = author_list.begin(); j != author_list.end(); j++) {
            if ((*i != *j)) {
                if (author_tree.find(*i) == author_tree.end()) {
                    vector<string> new_node;
                    new_node.push_back(*j);
                    author_tree[*i] = new_node;
                } else {
                    vector<string> nodes = author_tree[*i];
                    nodes.push_back(*j);
                    author_tree[*i] = nodes;
                }
            }
        }
    }
}

void assign_rank(map<string, int> &author_rank, map<string, vector<string> > author_tree) {
    author_rank["Erdos, P."] = 0;
    queue<string> author_queue;
    author_queue.push("Erdos, P.");
    while (!author_queue.empty()) {
        string author = author_queue.front();
        author_queue.pop();
        int rank = author_rank[author];
        int newRank = rank+1;
        vector<string> associated_authors = author_tree[author];
        for (int i = 0; i < associated_authors.size(); i++) {
            string a_author = associated_authors[i];
            if (author_rank.find(a_author) == author_rank.end()) {
                author_rank[a_author] = newRank;
                author_queue.push(a_author);
            }
        }
    }
}
