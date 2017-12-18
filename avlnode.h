#ifndef AVLNODE_H
#define AVLNODE_H
#include <iostream>
#include "wordobject.h"
#include "indexer.h"
using namespace std;
template <class T>
class AVLNode
{

private:

    //private data members


public:

    //default constructor
    AVLNode();

    //constructor with params
    AVLNode(T& element);
    AVLNode(const AVLNode& copy);
    AVLNode(T element, AVLNode<T>* left, AVLNode<T>* right);

    //overloaded "=" operator
    AVLNode& operator=(const AVLNode& copy);

    //setters and getters
    void setElement(const T& content);
    T getElement();

    //index
    T& index(string&);

    //destructor
    ~AVLNode();

    AVLNode<T>* left;
    AVLNode<T>* right;
    T element;

    int height;

};

//default constructor
template <class T>
AVLNode<T>::AVLNode(){

    element;
    left = nullptr;
    right = nullptr;
    height = 0;

}

//constructor with element passed in
template <class T>
AVLNode<T>::AVLNode(T& passedElement){

    element = passedElement;
    left = nullptr;
    right = nullptr;
    height = 0;

}

//copy constructor
template <class T>
AVLNode<T>::AVLNode(const AVLNode& copy){

    //sets variables equal to passed in AVLNode values
    element = copy.element;
    left = copy.left;
    right = copy.right;
    height = copy.height;

}

//constructor with multiple elements passed in
template <class T>
AVLNode<T>::AVLNode(T passedElement, AVLNode<T>* passedLeft, AVLNode<T>* passedRight){

    element = passedElement;
    left = passedLeft;
    right = passedRight;
    height = 0;

}

//overloaded the "=" operator
template <class T>
AVLNode<T>& AVLNode<T>::operator=(const AVLNode<T>& copy){

    element = copy.element;
    left = copy.left;
    right = copy.right;
    height = copy.height;
    return *this;

}

//sets element
template <class T>
void AVLNode<T>::setElement(const T &content){

    element = content;

}

//returns element
template <class T>
T AVLNode<T>::getElement(){

    return element;

}

//find certain word
template <class T>
T& AVLNode<T>::index(string& word) {
    if (element == word) {
        return element;
    }
    if (element < word) {
        return right->index(word);
    }
    return left->index(word);
}

//destructor
template <class T>
AVLNode<T>::~AVLNode(){

    if(right != nullptr){

        delete right;
        right = nullptr;

    }

    if(left != nullptr){

        delete left;
        left = nullptr;

    }

}

#endif // AVLNODE_H






///*
// * Owner: Sterling
// *
// * References:
// *  Find certain word: https://stackoverflow.com/questions/10955972/avl-trees-how-to-do-index-access
// *
// */

//#ifndef AVLNODE_H
//#define AVLNODE_H
//#include <iostream>
//using namespace std;
//template <class T>
//class AVLNode
//{

//private:

//    //private data members


//public:

//    //default constructor
//    AVLNode();

//    //constructor with params
//    AVLNode(T element);
//    AVLNode(const AVLNode& copy);
//    AVLNode(T element, AVLNode<T>* left, AVLNode<T>* right);

//    //overloaded "=" operator
//    AVLNode& operator=(const AVLNode& copy);

//    //setters and getters
//    void setElement(const T& content);
//    T getElement();

//    //index
//    T& index(string&);

//    //destructor
//    ~AVLNode();

//    AVLNode<T>* left;
//    AVLNode<T>* right;
//    T element;

//    int height;

//};

////default constructor
//template <class T>
//AVLNode<T>::AVLNode(){

//    element;
//    left = nullptr;
//    right = nullptr;
//    height = 0;

//}

////constructor with element passed in
//template <class T>
//AVLNode<T>::AVLNode(T passedElement){

//    element = passedElement;
//    left = nullptr;
//    right = nullptr;
//    height = 0;

//}

////copy constructor
//template <class T>
//AVLNode<T>::AVLNode(const AVLNode& copy){

//    //sets variables equal to passed in AVLNode values
//    element = copy.element;
//    left = copy.left;
//    right = copy.right;
//    height = copy.height;

//}

////constructor with multiple elements passed in
//template <class T>
//AVLNode<T>::AVLNode(T passedElement, AVLNode<T>* passedLeft, AVLNode<T>* passedRight){

//    element = passedElement;
//    left = passedLeft;
//    right = passedRight;
//    height = 0;

//}

////overloaded the "=" operator
//template <class T>
//AVLNode<T>& AVLNode<T>::operator=(const AVLNode<T>& copy){

//    element = copy.element;
//    left = copy.left;
//    right = copy.right;
//    height = copy.height;
//    return *this;

//}

////sets element
//template <class T>
//void AVLNode<T>::setElement(const T &content){

//    element = content;

//}

////returns element
//template <class T>
//T AVLNode<T>::getElement(){

//    return element;

//}

////find certain word
//template <class T>
//T& AVLNode<T>::index(string& word) {
//    if (element == word) {
//        return element;
//    }
//    if (element < word) {
//        return right->index(word);
//    }
//    return left->index(word);
//}

////destructor
//template <class T>
//AVLNode<T>::~AVLNode(){

//    if(right != nullptr){

//        delete right;
//        right = nullptr;

//    }

//    if(left != nullptr){

//        delete left;
//        left = nullptr;

//    }

//}

//#endif // AVLNODE_H
