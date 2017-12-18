#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "indexer.h"
#include "queryprocessor.h"
#include <vector>
#include <iostream>
using namespace std;

class IndexHandler {
public:
    IndexHandler();
    IndexHandler(int&, char* argv[]);

    void saveIndex();

    //interactive
    void setIndexType(char&);
    void processQuery(string&);
    void showResults(vector<int>&);
    int getNumWords();
    int getNumQuestions();

    //maintenance
    void passDocPath(char*);
    void clearIndex();

private:
    bool haveWordsToIndexFromPath;
    QueryProcessor queryProcessor;

    Indexer index;
    char indexType;
};

#endif // INDEXHANDLER_H
