#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashNode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

template <class K, class V>
class HashTable {
public:
    void print();

    HashTable();
    ~HashTable();

    vector<V>& getValuesForKey(K&);
    void insert(K&, V&);
    void insert(K&, vector<V>&);
    void removeKey(K&);
    void clear();

    void saveTable(ofstream&);

    vector<V>& operator[](K&);

    template <class U, class Y> friend class HashNode;
private:
    int hashFunction(string&);
    int hashFunction(int&);

    HashNode<K,V>** table;
    int capacity;
    int size;
};

template <class K, class V>
void HashTable<K,V>::print() {
    if (table == nullptr) {
        cout << "Empty Table" << endl;
    }
    else {
        cout << "stuff in table" << endl;
    }
}

template <class K, class V>
HashTable<K,V>::HashTable() {
    capacity = 5000; //choose default table size
    size = 0;
    table = new HashNode<K,V>*[capacity];
    //iterate thru table, set each row to nullptr
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

template <class K, class V>
HashTable<K,V>::~HashTable() {
    clear();
}

template <class K, class V>
vector<V>& HashTable<K,V>::getValuesForKey(K& key) {
    //make sure in lowercase

    int hashKey = hashFunction(key);
    HashNode<K,V>* checkMe = table[hashKey];
    while (checkMe != nullptr) {
        if (checkMe->key == key) {
            return checkMe->values;
        }
        checkMe = checkMe->next;
    }
}

template <class K, class V>
void HashTable<K,V>::insert(K& setKey, V& setValue) {
    int hashKey = hashFunction(setKey);
//    cout << hashKey << ": " << setKey << ", " << setValue << endl;
    HashNode<K,V>* checkMe = table[hashKey];
    HashNode<K,V>* prev = nullptr;
    //iterate thru table until find setKey
    while (checkMe != nullptr && checkMe->key != setKey) {
        prev = checkMe;
        checkMe = checkMe->next;
    }
    //if reach end of table and don't find setKey
    if (checkMe == nullptr) {
        //create new node
        checkMe = new HashNode<K,V>(setKey, setValue);
        //if first element in table
        if (prev == nullptr) {
            table[hashKey] = checkMe;
        }
        else {
            prev->next = checkMe;
        }
    }
    //if find setKey
    else {
        //add value to list of values for key
        if (checkMe->key == setKey) {
            checkMe->values.push_back(setValue);
        }
        else {
            if (checkMe->next == nullptr) {
                checkMe->next = new HashNode<K,V>(setKey, setValue);
            }
            else {
                while (checkMe->next != nullptr) {
                    checkMe = checkMe->next;
                    if (checkMe->key == setKey) {
                        checkMe->values.push_back(setValue);
                        break;
                    }
                    if (checkMe->next == nullptr) {
                        checkMe->next = new HashNode<K,V>(setKey, setValue);
                        break;
                    }
                }
            }
        }

    }
}

template <class K, class V>
void HashTable<K,V>::insert(K& setKey, vector<V>& setVector) {
    int hashKey = hashFunction(setKey);
    HashNode<K,V>* checkMe = table[hashKey];
    HashNode<K,V>* prev = nullptr;
    //iterate thru table until find setKey
    while (checkMe != nullptr && checkMe->key != setKey) {
        prev = checkMe;
        checkMe = checkMe->next;
    }
    //if reach end of table and don't find setKey
    if (checkMe == nullptr) {
        //create new node
        checkMe = new HashNode<K,V>(setKey, setVector);
        //if first element in table
        if (prev == nullptr) {
            table[hashKey] = checkMe;
        }
        else {
            prev->next = checkMe;
        }
    }
    //if find setKey
    else {
        //add value to list of values for key
        if (checkMe->key == setKey) {
            checkMe->values = setVector;
        }
        else {
            if (checkMe->next == nullptr) {
                checkMe->next = new HashNode<K,V>(setKey, setVector);
            }
            else {
                while (checkMe->next != nullptr) {
                    checkMe = checkMe->next;
                    if (checkMe->key == setKey) {
                        checkMe->values = setVector;
                        break;
                    }
                    if (checkMe->next == nullptr) {
                        checkMe->next = new HashNode<K,V>(setKey, setVector);
                        break;
                    }
                }
            }
        }
    }
}

template <class K, class V>
void HashTable<K,V>::removeKey(K& removeKey) {
    int hashKey = hashFunction(removeKey);
    HashNode<K,V>* checkMe = table[hashKey];
    HashNode<K,V>* prev = nullptr;
    //iterate thru table until find setKey
    while (checkMe != nullptr && checkMe->key != removeKey) {
        prev = checkMe;
        checkMe = checkMe->next;
    }
    //if reach end of table and don't find removeKey
    if (checkMe == nullptr) {
        return;
    }
    else {
        //if removing first element of table
        if (prev == nullptr) {
            table[hashKey] = checkMe->next;
        }
        else {
            prev->next = checkMe->next;
        }
        delete checkMe;
    }
}

template <class K, class V>
void HashTable<K,V>::clear() {
    if (table != nullptr) {
        //iterate thru table, delete elements
        for (int i = 0; i < capacity; i++) {
            if (table[i] != nullptr) {
                if (table[i]->next == nullptr) {
                    delete table[i];
                }
                else {
                    HashNode<K,V>* temp = table[i];
                    HashNode<K,V>* prev = table[i];
                    while (temp->next != nullptr) {
                        temp = temp->next;
                        delete prev;
                        prev = temp;
                    }
                    delete temp;
                }
                table[i] = nullptr;
            }
        }
    }
}

template <class K, class V>
void HashTable<K,V>::saveTable(ofstream& outputFile) {
    //Format:
    //word
    //id
    //NEW_ELEMENT
    //word
    //id
    for (int i = 0; i < capacity; i++) {
        HashNode<K,V>* temp = table[i];
        while (temp != nullptr) {
            outputFile << temp->key << "\n";
            int tempSize = temp->values.size();
            for (int j = 0; j < tempSize; j++) {
                outputFile << temp->values[j] << "\n";
            }
            temp = temp->next;
            outputFile << "NEW_ELEMENT\n";
        }
    }
}

template <class K, class V>
vector<V>& HashTable<K,V>::operator[](K& index) {
    int hashKey = hashFunction(index);
    if (table[hashKey] != nullptr) {
        if (table[hashKey]->key == index) {
            return table[hashKey]->values;
        }
        else {
            HashNode<K,V>* temp = table[hashKey];
            while (temp->next != nullptr) {
                if (temp->key == index) {
                    return temp->values;
                }
                temp = temp->next;
            }
            //if matches no specific keys just return first value in list
            return table[hashKey]->values;
        }
    }
}

//hashfuntion to deal w string keys
template <class K, class V>
int HashTable<K,V>::hashFunction(string& keyword) {
    int sum = 0;
    int length = keyword.length();
    for (int i = 0; i < length; i++) {
        sum += int(keyword[i]);
    }
    if (sum > capacity) {
        sum %= capacity;
    }
    return sum;
}

template <class K, class V>
int HashTable<K,V>::hashFunction(int& keyNum) {
    return keyNum % capacity;
}

#endif // HASHTABLE_H
