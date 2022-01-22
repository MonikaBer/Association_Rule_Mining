#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include "Logger.hpp"
using namespace std;

set<int> splitStringToTransaction(string text, string delimiter) {
    size_t pos = 0;
    string token;
    int intToken;
    set<int> t;
    while ((pos = text.find(delimiter)) != string::npos) {
        token = text.substr(0, pos);
        intToken = stoi(token);
        t.insert(intToken);
        text.erase(0, pos + delimiter.length());
    }
    intToken = stoi(text);
    t.insert(intToken);
    return t;
}

pair<int, int> splitStringToTaxonomyRow(string text, string delimiter) {
    size_t pos = text.find(delimiter);
    string token1 = text.substr(0, pos);
    string token2 = text.substr(pos + delimiter.length(), text.length());
    int intToken1 = stoi(token1);
    int intToken2 = stoi(token2);
    pair<int, int> tax = make_pair(intToken1, intToken2);
    return tax;
}

pair<int, string> splitStringToLabelsRow(string text, string delimiter) {
    size_t pos = text.find(delimiter);
    string token1 = text.substr(0, pos);
    string token2 = text.substr(pos + delimiter.length(), text.length());
    int intToken = stoi(token1);
    pair<int, string> label = make_pair(intToken, token2);
    return label;
}

void showTransactions(map<int, set<int>> transactions) {
    map<int, set<int>>::iterator mapIt;
    cout << "TRANSACTIONS\n";
    for (mapIt = transactions.begin(); mapIt != transactions.end(); ++mapIt) {
        set<int>::iterator setIt;
        cout << mapIt->first << ": ";
        for (setIt = mapIt->second.begin(); setIt != mapIt->second.end(); ++ setIt) {
            cout << *setIt << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void showTaxonomy(map<int, int> taxonomy) {
    map<int, int>::iterator it;
    cout << "TAXONOMY\n";
    int counter = 0;
    for (it = taxonomy.begin(); it != taxonomy.end(); ++it) {
        cout << it->first << ", " << it->second << endl;
        ++counter;
    }
    cout << "Map length: " << counter << endl << endl;
}

void showLabels(map<int, string> labels) {
    map<int, string>::iterator it;
    cout << "LABELS\n";
    int counter = 0;
    for (it = labels.begin(); it != labels.end(); ++it) {
        cout << it->first << ", " << it->second << endl;
        ++counter;
    }
    cout << "Map length: " << counter << endl << endl;
}


int main(int argc, char** argv) {
    Logger logger;
    if ( argc != 4 ) {
        logger << Logger::LogType::LOG_ERROR << "usage: ./main <path to transactions> <path to taxonomy> <path to labels>\n";
        return 1;
    }

    //transactions file
    ifstream transactionsFile(argv[1]);
    if (!transactionsFile.is_open()) {
        logger << Logger::LogType::LOG_ERROR << "Cannot open file: " << argv[1];
        return 1;
    }

    string line;

    //transactions map: nr -> transaction
    map<int, set<int>> transactions;
    int nr = 1;
    while (getline(transactionsFile, line)) {
        set<int> t = splitStringToTransaction(line, " ");
        transactions[nr] = t;
        ++nr;
    }

    //taxonomy file
    ifstream taxonomyFile(argv[2]);
    if (!taxonomyFile.is_open()) {
        logger << Logger::LogType::LOG_ERROR << "Cannot open file: " << argv[2];
        return 1;
    }

    //taxonomy map: item1 -> item2 (item1 below item2 in the taxonomy)
    //item2 -> item3
    map<int, int> taxonomy;
    while (getline(taxonomyFile, line)) {
        pair<int, int> tax = splitStringToTaxonomyRow(line, ",");
        taxonomy[tax.first] = tax.second;
    }

    //file with labels
    ifstream labelsFile(argv[3]);
    if (!labelsFile.is_open()) {
        logger << Logger::LogType::LOG_ERROR << "Cannot open file: " << argv[3];
        return 1;
    }

    //labels map: id -> label
    map<int, string> labels;
    while (getline(labelsFile, line)) {
        pair<int, string> label = splitStringToLabelsRow(line, ",");
        labels[label.first] = label.second;
    }

    showTransactions(transactions);
    showTaxonomy(taxonomy);
    showLabels(labels);

    //determine tidlists for itemsets and their supports




    return 0;
}
