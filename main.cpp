#include<bits/stdc++.h>
using namespace std;

map<string, map<string, int>> invertedIndex;
vector<string> documents = { "doc1.txt", "doc2.txt", "doc3.txt" };

string preProcess(string word) { // removes punctuation and converts words into lowercase
    string clean = "";

    for (char c : word) {
        if (isalnum(c)) {
            clean += tolower(c);
        }
    }
    return clean;
}

void buildIndex() {
    for (string file : documents) {

        ifstream fopen(file);
        string word;

        while (fopen >> word) {
            word = preProcess(word);

            if (word != "") {
                invertedIndex[word][file]++;
            }
        }

        fopen.close();
    }
}

void searchWord(string query) {
    query = preProcess(query);

    if (invertedIndex.find(query) == invertedIndex.end()) {
        cout << "Word not found\n";
        return;
    }

    vector<pair<string, int>> results;

    for (auto& doc : invertedIndex[query]) {
        results.push_back(doc);
    }

    sort(results.begin(), results.end(), [](pair<string, int> a, pair<string, int> b) {
        return a.second > b.second;
        });

    cout << "Search results\n";

    for (auto& res : results) {
        cout << res.first << "(Frequency : " << res.second << " )\n";
    }
}

int main() {
    buildIndex();
    string query;

    while (1) {
        cout << "Enter search word (type Q to quit): ";
        cin >> query;

        if (query == "Q") {
            break;
        }

        searchWord(query);
    }

    return 0;
}