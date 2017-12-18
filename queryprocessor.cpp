#include "queryprocessor.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

QueryProcessor::QueryProcessor() {}

vector<string>& QueryProcessor::startProcessingQuery(string& userEnteredQuery) {
    wordsToSearchFor.clear();
    query = userEnteredQuery;
    //check if one-word query
    size_t found = query.find(" ");
    //if multiple words
    if (found != string::npos) {
        separateWords(userEnteredQuery, found);
    }
    else {
        if (!isStopWord(query)) {
            wordsToSearchFor.push_back(query);
        }
    }
    return wordsToSearchFor;
}

void QueryProcessor::separateWords(string& userQuery, size_t& foundPosition) {
    string temp = userQuery.substr(0, foundPosition);
    if (!isStopWord(temp) && temp != "OR") {
        convertToLowerCase(temp);
        stemmer.stemWord(temp);
        wordsToSearchFor.push_back(temp);
    }
    string restOfWord = userQuery.substr(foundPosition + 1);
    bool isSpace = true;
    while (isSpace) {
        foundPosition = restOfWord.find(" ");
        //if more spaces found
        if (foundPosition != string::npos) {
            string tempRest;
            temp = restOfWord.substr(0, foundPosition);
            if (!isStopWord(temp)) {
                convertToLowerCase(temp);
                stemmer.stemWord(temp);
                wordsToSearchFor.push_back(temp);
            }
            tempRest = restOfWord.substr(foundPosition + 1);
            restOfWord = tempRest;
        }
        //if no more spaces found
        else {
            isSpace = false;
        }
    }
    if (!isStopWord(restOfWord)) {
        convertToLowerCase(temp);
        stemmer.stemWord(restOfWord);
        wordsToSearchFor.push_back(restOfWord);
    }
}

bool QueryProcessor::isStopWord(string& word){
    for(int i = 0; i < stopWordList.size(); i++){
        if(word == stopWordList[i]){
            return true;
        }
    }
    return false;
}

void QueryProcessor::convertToLowerCase(string& convertMe) {
    if (convertMe != "AND" && convertMe != "OR" && convertMe != "NOT") {
        transform(convertMe.begin(), convertMe.end(), convertMe.begin(), ::tolower);
    }
}
