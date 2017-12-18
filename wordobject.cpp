#include "wordobject.h"

WordObject::WordObject() {
    word = "";
    numOfIDs = 0;
}

WordObject::WordObject(string& wordToSet, int& idNum) {
    word = wordToSet;
    idNums.push_back(idNum);
    numOfIDs = 1;
}

WordObject::WordObject(string& wordToSet, vector<int>& idNumsToSet) {
    word = wordToSet;
    idNums = idNumsToSet;
    numOfIDs = idNumsToSet.size();
}

void WordObject::addID(int& idNum) {
    idNums.push_back(idNum);
    numOfIDs++;
}

vector<int>& WordObject::getIDs() {
    return idNums;
}

WordObject& WordObject::operator=(const WordObject& rhs) {
    word = rhs.word;
    numOfIDs = rhs.numOfIDs;
    idNums = rhs.idNums;
    return *this;
}

bool WordObject::operator<(const WordObject& rhs) const {
    if (word < rhs.word) {
        return true;
    }
    return false;
}

bool WordObject::operator<(const string& rhs) const {
    if (word < rhs) {
        return true;
    }
    return false;
}

bool WordObject::operator>(WordObject& rhs) {
    if (word > rhs.word) {
        return true;
    }
    return false;
}

bool WordObject::operator>(string& rhs) {
    if (word > rhs) {
        return true;
    }
    return false;
}

bool WordObject::operator==(WordObject& rhs) {
    if (word == rhs.word) {
        return true;
    }
    return false;
}

bool WordObject::operator==(string& rhs) {
    if (word == rhs) {
        return true;
    }
    return false;
}

WordObject& WordObject::operator+(const WordObject& rhs) {
    //if same word, different id numbers
    if (idNums[numOfIDs - 1] != rhs.idNums[0]) {
        idNums.push_back(rhs.idNums[0]);
        numOfIDs++;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& output,  WordObject& object)
{
    //FORMAT FOR SAVING FILE:

    //word
    //idnumber
    //NEW_ELEMENT

    //ex:
    //branch
    //90
    //214
    //8899
    //NEW_ELEMENT
    //spaghetti
    //100
    //1267

    output << object.word << "\n";
    for (int i = 0; i < object.numOfIDs; i++) {
        output << object.idNums[i] << "\n";
    }
    return output;
}
