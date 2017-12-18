#include "indexer.h"
#include "documentParser.h"
#include "wordobject.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <locale>
using namespace std;
Indexer::Indexer() {
    saveFilePath = "../../lib/Index.txt";
    questionsIndexed = 0;
}

void Indexer::passCommandArgs(char *argv[]) {
    arg = argv;
}

void Indexer::IndexQuestion(char* input_file){
    CsvParser *csvparser = CsvParser_new(input_file, ",", 1);
    CsvRow *row;

    while ((row = CsvParser_getRow(csvparser))) {
        row = CsvParser_getRow(csvparser);

        if (row != nullptr) {
             char **rowFields = CsvParser_getFields(row);
             char *title = rowFields[5];
             char *body = rowFields[6];
             char* ids = rowFields[1];

             string s = string(title);
             string b = string(body);
             string idString = string(ids);
             int id = stoi(idString);

             trunkateWord(title, id);
             trunkateWord(body, id);
             questionsIndexed++;
         }
    }

    if (row != nullptr) {
        CsvParser_destroy_row(row);
    }

    CsvParser_destroy(csvparser);
}

void Indexer::trunkateWord(string title, int& idNum){
    const std::string puncts = "[];./{}:\"?><`~!_";
              std::string result;

              for (const auto& ch : title)
              {
                  bool found = false;
                  for (const auto& p : puncts)
                  {
                      if (ch == p)
                      {
                          found = true;
                          break;
                      }
                  }

                  if (!found)
                      result += ch;
              }


    bool checkIfStopword = false;
    stringstream ss;
    ss << result;
    istringstream iss(result);
    do
    {
        string tokString;
        iss >> tokString;
        if(tokString == ""){
            break;
        }

        //convert to lwrcase
        transform(tokString.begin(), tokString.end(), tokString.begin(), ::tolower);

        checkIfStopword = isStopWord(tokString);
        if(checkIfStopword == false){

            //stem word
            stemmer.stemWord(tokString);

            if(tokString == "") {
                break;
            }

            storeInAVLTree(tokString, idNum);
            storeInHashTable(tokString, idNum);
        }

    } while (iss);

}

bool Indexer::isStopWord(string tokString){
    int stopSize = stopWordList.size();
    for(int i = 0; i < stopSize; i++){
        if(tokString == stopWordList[i]){
            return true;
        }
    }
    return false;
}

void Indexer::IndexTags(char* input_file){

     CsvParser *csvparser = CsvParser_new(input_file, ",", 1);
     CsvRow *row;

     while ((row = CsvParser_getRow(csvparser)) ) {
         char **rowFields = CsvParser_getFields(row);

         char* tag = rowFields[2];
         char* ids = rowFields[1];

         string s = string(tag);
         string idString = string(ids);
         int id = stoi(idString);

         storeInAVLTree(s, id);
         storeInHashTable(s, id);

        if (row != nullptr) {
            CsvParser_destroy_row(row);
        }
     }
     CsvParser_destroy(csvparser);
}

void Indexer::storeInAVLTree(string& wordToAdd, int& idNumToAdd) {
    WordObject tempObject(wordToAdd, idNumToAdd);
    tree.insert(tempObject);
}

void Indexer::storeInHashTable(string& word, int& idNum) {
    table.insert(word, idNum);
}

void Indexer::clearIndex() {
    tree.clearTree();
    table.clear();
    questionsIndexed = 0;
}

//get num of elements in AVLTree Index
int Indexer::getAmountWords() {
    return tree.getElementCount();
}

//get nums qs indexed
int Indexer::getAmountQuestions() {
    return questionsIndexed;
}

//get vector of IDNums from Hash Table Index
vector<int> Indexer::getIDNumsHash(string& key) {
    return table.getValuesForKey(key);
}

//get vector of IDnums from AVL Tree Index
vector<int> Indexer::getIDNumsAVL(string& word) {
    WordObject temp = tree.findWord(word);
    return temp.getIDs();
}

//save index to file
void Indexer::saveIndexToFile() {
    //save index to output file
    ofstream outputFile(saveFilePath, ios::out);
    table.saveTable(outputFile);
}

void Indexer::readIndexFromFile(char type) {

    //read in both indexes and store in tree/table
    ifstream inputFile(saveFilePath, ios::in);
    bool isWord = false;
    questionsIndexed = 1264215;
    string word;
    vector<int> idNumsFromFile;
    string line;
    inputFile >> word;
    while (inputFile >> line) {
        //if finished reading idnums of word
        if (line == "NEW_ELEMENT") {
            //if inserting into AVLTree
            if (type == 'a') {
                //make wordobject of prev word and idnums and add to tree
                WordObject insertMe(word, idNumsFromFile);
                tree.insert(insertMe);
            }
            //if inserting into HashTable
            else {
                //add to table
                table.insert(word, idNumsFromFile);
            }
            isWord = true;
            idNumsFromFile.clear();
        }
        //if line == word to be indexed
        else if (isWord) {
            word = line;
            isWord = false;
        }
        //if line == idNum to be indexed
        else {
            string tempIdString = line;
            int firstNum = (int)(tempIdString.at(0));

            //check to make sure works correctly
            if (firstNum > 47 && firstNum < 58) {
                int tempIDNum = stoi(tempIdString);
                idNumsFromFile.push_back(tempIDNum);
            }
            else {
                cout << "ERROR- thinks this is ID: " << tempIdString << endl;
            }
        }
    }
}

void Indexer::checkID(int suggestedId,  char* input_file) {
    CsvParser *csvparser = CsvParser_new(input_file, ",", 1);

    CsvRow *row;
    vector<char*> tempVec;
    int numberOfRunThroughs = suggestedIdNums.size();
    while ((row = CsvParser_getRow(csvparser))) {
        row = CsvParser_getRow(csvparser);
        if (row != nullptr) {
            char **rowFields = CsvParser_getFields(row);
                 char* ids = rowFields[1];
                 string idString = string(ids);
                 int id = stoi(idString);
                 if(suggestedId == id){
                    tempVec.push_back(rowFields[1]);
                    tempVec.push_back(rowFields[2]);
                    tempVec.push_back(rowFields[3]);
                    tempVec.push_back(rowFields[4]);
                    tempVec.push_back(rowFields[5]);
                    tempVec.push_back(rowFields[6]);
                    tempVec.push_back(rowFields[7]);
                    printVector.push_back(tempVec);
                    idParseCount++;
                    if(numberOfRunThroughs == idParseCount){
                        printMenu(printVector);
                    }
                    break;
                 }
            }
       }
   CsvParser_destroy(csvparser);

}

void Indexer::printMenu(vector<vector<char*>> printVec){
    int answer = 0;
    int row = 1;
    int count = suggestedIdNums.size();

    cout << "\nQuestion Titles:\n" << endl;
    int printSize = printVec.size();
    for(int j = 0; j < printSize; j++){
        cout << row << ")" << "\t" << printVec[j][4] << endl;
        row++;
        count--;
        if(count == 0){
            break;
        }
     }

    cout << "\n" << "Please choose a question you would like to expand: ";
    cin >> answer;
    cout << endl;

    if (answer != 1 && answer !=2 && answer !=3 && answer !=4 && answer!=5 && answer!=6
            && answer!=7 && answer!=8 && answer!=9 && answer !=10 && answer!=11
            && answer!=12 && answer!=13 && answer!=14 && answer!=15){
        cerr << "THE QUESTION NUMBER YOU ENTERED IS INCORRECT" << endl;
    }

    cout << "==================================================================" << endl;
    cout << "Now displaying...\n\n===========\nQUESTION " << answer << ": \n===========\n" << endl;
    cout << "QUESTION ID: \t\t" << printVec[answer-1][0] << "\n" << endl;
    cout << "OWNER USER ID: \t\t" << printVec[answer-1][1] << "\n" << endl;
    cout << "CREATION DATE: \t\t" << printVec[answer-1][2] << "\n" << endl;
    cout << "QUESTION SCORE: \t" << printVec[answer-1][3] << "\n" << endl;
    cout << "QUESTION TITLE: \n\n" << printVec[answer-1][4] << "\n" << endl;
    cout << "QUESTION BODY: \n\n" << printVec[answer-1][5] << "\n" << endl;
    cout << "QUESTION CODE: \n\n\t" << printVec[answer-1][6] << "\n" << endl;
    cout << "==================================================================" << endl;

}


void Indexer::showResults(vector<int> ids) {
    idParseCount = 0;
    int i = 0;
    int idSize = ids.size();
    printVector.clear();
    suggestedIdNums = ids;
    while (idParseCount < idSize) {
           if(ids[i] >= 80 && ids[i] <= 404280){
               //2008 questions
                checkID(ids[i], arg[1]);
           }
           else if((ids[i] >= 404430 && ids[i] <= 1987470) || ids[i] == 2274530){
               //2009 questions
               checkID(ids[i], arg[3]);
           }
           else if((ids[i] >= 1987570 && ids[i] <= 4572720) || ids[i] == 4771180 || ids[i] == 5658850
                   || ids[i] == 6151030 || ids[i] == 7126700 || ids[i] == 941140 || ids[i] == 12342790){
               //2010 questions
               checkID(ids[i], arg[5]);
           }
           else if((ids[i] >= 4572790 && ids[i] <= 8691130) || ids[i] == 10260400 || ids[i] == 11960540
                   || ids[i] == 12040240 || ids[i] == 12125980 || ids[i] == 13105980){
               //2011 questions
               checkID(ids[i], arg[7]);
           }
           else if(ids[i] >= 8691180 && ids[i] <= 14106820){
               //2012 questions
               checkID(ids[i], arg[9]);
           }
           else if(ids[i] >= 14106920 && ids[i] <= 20864390){
               //2013 questions
               checkID(ids[i], arg[11]);
           }
           else if(ids[i] >= 20864430 && ids[i] <= 27727360){
               //2014 questions
               checkID(ids[i], arg[13]);
           }
           else if(ids[i] >= 27727410 && ids[i] <= 34552540){
               //2015 questions
               checkID(ids[i], arg[15]);
           }
           else{
               //2016 questions
               checkID(ids[i], arg[17]);
           }

        i++;
        if (i > idSize) {
            printMenu(printVector);
            break;
        }
    }
}
