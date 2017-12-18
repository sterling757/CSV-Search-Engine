#ifndef WORDOBJECT_H
#define WORDOBJECT_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class WordObject
{
public:
    WordObject();
    WordObject(string&, int&);
    WordObject(string&, vector<int>&);

    void addID(int&);
    vector<int>& getIDs();

    WordObject& operator=(const WordObject&);
    bool operator<(const WordObject&) const;
    bool operator<(const string&) const;
    bool operator>(WordObject&);
    bool operator>(string&);
    bool operator==(WordObject&);
    bool operator==(string&);
    WordObject& operator+(const WordObject&);

    friend std::ostream& operator<<(std::ostream&, WordObject&);
private:
    string word;
    vector<int> idNums;
    int numOfIDs;
};

#endif // WORDOBJECT_H
