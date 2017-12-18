#include "indexhandler.h"
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

IndexHandler::IndexHandler() {
    haveWordsToIndexFromPath = false;
    indexType = ' ';
}

IndexHandler::IndexHandler(int& argc, char* argv[]) {
    haveWordsToIndexFromPath = false;
    index.passCommandArgs(argv);
    //for command line args
//    for (int i = 1; i < argc; i++) {
//        //if odd number, working with questions
//        if (i % 2 != 0) {
//            index.IndexQuestion(argv[i]);
//        }
//        //if even number, working with tags
//        else {
//            index.IndexTags(argv[i]);
//        }
//    }

    //load index from .txt when start program
    index.readIndexFromFile('a');
    index.readIndexFromFile('h');

}

void IndexHandler::saveIndex() {
    index.saveIndexToFile();
}

/*
 *
 *
 *          Interactive Mode
 *
 *
 */

void IndexHandler::setIndexType(char& type) {
    //if user chooses avl index
    if (type == 'a') {
        indexType = 'a';
    }
    //if user chooses hash table index
    else {
        indexType = 'h';
    }


    if (haveWordsToIndexFromPath) {
        //add to index (vector of objects to be indexed) ... somehow
    }
}

void IndexHandler::processQuery(string& query) {
    bool isNot = false;
    vector<string> searchTerms;
    searchTerms = queryProcessor.startProcessingQuery(query);
    int size = searchTerms.size();
    if (searchTerms.size() == 0) {
        cout << "\"" << query << "\" is a stop word, and therefore not stored in the index" << endl;
    }
    if (searchTerms[0] == "AND") {
        vector<int> idNums1;
        vector<int> idNums2;
        vector<int> combo;
        int searchSize = searchTerms.size();
        for (int i = 1; i < searchSize; i++) {
            if (i == 1) {
                if (indexType == 'a') {
                    idNums1 = index.getIDNumsAVL(searchTerms[1]);
                    idNums2 = index.getIDNumsAVL(searchTerms[2]);
                }
                else {
                    idNums1 = index.getIDNumsHash(searchTerms[1]);
                    idNums2 = index.getIDNumsHash(searchTerms[2]);
                }
                int size1 = idNums1.size();
                int size2 = idNums2.size();
                for (int j = 0; j < size1; j++) {
                    for (int k = 0; k < size2; k++) {
                        if (idNums1[j] == idNums2[k]) {
                            combo.push_back(idNums1[j]);
                        }
                    }
                }
            }
            else if (searchTerms[i] == "NOT") {
                isNot = true;
            }
            else {
                if (i == 2) {
                    continue;
                }
                else if (isNot) {
                    if (indexType == 'a') {
                        idNums1 = index.getIDNumsAVL(searchTerms[i]);
                    }
                    else {
                        idNums1 = index.getIDNumsHash(searchTerms[i]);
                    }
                    idNums2.clear();
                    int comboSize = combo.size();
                    for (int j = 0; j < comboSize; j++) {
                        bool inCombo = false;
                        int size1 = idNums1.size();
                        for (int k = 0; k < size1; k++) {
                            if (combo[j] == idNums1[k]) {
                                inCombo = true;
                                break;
                            }
                        }
                        if (!inCombo) {
                            idNums2.push_back(combo[j]);
                        }
                    }
                    isNot = false;
                    combo = idNums2;
                }
                else {
                    if (indexType == 'a') {
                        idNums1 = index.getIDNumsAVL(searchTerms[i]);
                    }
                    else {
                        idNums1 = index.getIDNumsHash(searchTerms[i]);
                    }
                    idNums2.clear();
                    if (!isNot) {
                        int size1 = idNums1.size();
                        int comboSize = combo.size();
                        for (int j = 0; j < size1; j++) {
                            for (int k = 0; k < comboSize; k++) {
                                if (idNums1[j] == combo[k]) {
                                    idNums2.push_back(idNums1[j]);
                                }
                            }
                        }
                    }
                    combo = idNums2;
                }
            }
        }
        showResults(combo);
    }
    else {
        vector<int> allIDNums;
        vector<int> idNots;
        vector<int> newIDNums;
        for (int i = 0; i < size; i++) {
            if (searchTerms.size() == 1) {
                if (indexType == 'a') {
                    allIDNums = index.getIDNumsAVL(searchTerms[0]);
                }
                else {
                    allIDNums = index.getIDNumsHash(searchTerms[0]);
                }
                break;
            }
            if (isNot) {
                newIDNums.clear();
                if (indexType == 'a') {
                    idNots = index.getIDNumsAVL(searchTerms[i]);
                }
                else {
                    idNots = index.getIDNumsHash(searchTerms[i]);
                }
                int allIDNumsSize = allIDNums.size();
                int idNotsSize = idNots.size();
                for (int j = 0; j < allIDNumsSize; j++) {
                    bool inAllIDNums = false;
                    for (int k = 0; k < idNotsSize; k++) {
                        if (allIDNums[j] == idNots[k]) {
                            inAllIDNums = true;
                            break;
                        }
                    }
                    if (!inAllIDNums) {
                        newIDNums.push_back(allIDNums[j]);
                    }
                }
                isNot = false;
                allIDNums = newIDNums;
            }
            else {
                if (searchTerms[i] == "NOT") {
                    isNot = true;
                    continue;
                }
                if (indexType == 'a') {
                    allIDNums = index.getIDNumsAVL(searchTerms[i]);
                }
                else {
                    allIDNums = index.getIDNumsHash(searchTerms[i]);
                }
            }
        }
        showResults(allIDNums);
        cout << endl;
    }
}

void IndexHandler::showResults(vector<int>& idNumsToRetrieve) {
    //remove duplicates
    set<int> s(idNumsToRetrieve.begin(), idNumsToRetrieve.end());
    idNumsToRetrieve.assign(s.begin(), s.end());

    if (idNumsToRetrieve.size() > 15) {
        vector<int> temp;
        for (int i = 0; i < 15; i++) {
            temp.push_back(idNumsToRetrieve[i]);
        }
        idNumsToRetrieve.assign(temp.begin(), temp.end());
    }

    index.showResults(idNumsToRetrieve);
}

int IndexHandler::getNumWords() {
    return index.getAmountWords();
}

int IndexHandler::getNumQuestions() {
    return index.getAmountQuestions();
}

/*
 *
 *
 *          Maintenance Mode
 *
 *
 */

void IndexHandler::passDocPath(char* path) {
    string choice;
    cout << "Is this file for questions or tags? Please enter Q for questions and T for tags\nChoice: ";
    cin >> choice;

    if (choice == "Q" || choice == "q") {
        index.IndexQuestion(path);
    }
    else {
        index.IndexTags(path);
    }
}

void IndexHandler::clearIndex() {
    index.clearIndex();
}
