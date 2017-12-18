#ifndef AVLTREE_H
#define AVLTREE_H
#include "avlnode.h"
#include "HashTable.h"
#include "wordobject.h"
#include "indexer.h"
#include <iostream>
#include <fstream>

template <class T>
class AVLTree
{

private:

    friend class AVLNode<T>;
    int elementCount;
    AVLNode<T>* root;
    AVLNode<T>* copy(AVLNode<T>* c);

    int height(AVLNode<T>*);
    int max(int, int);
    void rotateWithLeftChild(AVLNode<T>*&);
    void rotateWithRightChild(AVLNode<T>*&);
    void doubleWithLeftChild(AVLNode<T>*&);
    void doubleWithRightChild(AVLNode<T>*&);

    void saveTree(std::ofstream&, AVLNode<T>*&);

public:

    AVLTree();
    AVLTree(const AVLTree&);
    AVLTree& operator =(const AVLTree& e);

    T& findWord(string&);
    T& findMax();
    T& findMax(T node, T result);
    bool contains(const T&);
    bool isEmpty();
    bool isBalenced(AVLNode<T>* node);
    void clearTree();
    AVLNode<T>* getRoot();
    void insert(const T& content, AVLNode<T>*& node);
    void insert(const T& content);
    int getElementCount();
    std::ostream& printTree(std::ostream& o,  AVLNode<T>* node);

    void saveTree(std::ofstream&);

    template <class U>
    friend std::ostream& operator<<(std::ostream& o,  AVLTree<U>& tree);
    ~AVLTree();

};

//default constructor
template <class T>
AVLTree<T>::AVLTree(){

    root = nullptr;

}

template <class T>
AVLTree<T>::AVLTree(const AVLTree & rhs){

    root = nullptr;
    *this = rhs;

}

template <class T>
T& AVLTree<T>:: findMax(){

     //return root->index()

}

template <class T>
T& AVLTree<T>::findMax(T node, T result){
    if (node == nullptr){
            return result;
        }
        if (node.value > result.value ||
                (node.value == result.value && node.key.compareTo(result.key) < 0)){
            result = node;
        }
        result = findMax(node.left,result);
        result = findMax(node.right,result);
        return result;
}

template <class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree& e){

    clearTree();
    root = copy(e.root);
    elementCount = e.elementCount;
    return *this;

}

template <class T>
AVLNode<T>* AVLTree<T>::copy(AVLNode<T> *c){

    if(c == nullptr){
        return nullptr;
    }
    return new AVLNode<T>(c->element, copy(c->left), c->right);

}



template <class T>
T& AVLTree<T>::findWord(string& word) {
    return root->index(word);
}

template <class T>
int AVLTree<T>::height(AVLNode<T> * node){
    if(node == nullptr){
        return -1;
    }
    else
        return node->height;
}

template <class T>
int AVLTree<T>::max(int lhs, int rhs){
    if(lhs > rhs){
        return lhs;
    }
    else
        return rhs;
}

template <class T>
void AVLTree<T>::insert(const T &content){

    insert(content, root);

}

template <class T>
void AVLTree<T>::insert(const T& content, AVLNode<T>*& node){

    if(node == nullptr){
        node = new AVLNode<T>(content, nullptr, nullptr);
        elementCount++;
    }

    else if(content < node->getElement()){

            insert(content, node->left);
            if(height(node->left) - height(node->right) == 2){
                //case 1
                if(content < node->left->getElement())
                    rotateWithLeftChild(node);
                //case 2
                else
                    doubleWithLeftChild(node);
            }
    }

    else if(node->getElement() < content){

            insert(content, node->right);

            if(height(node->right) - height(node->left) == 2){

                if(node->right->getElement() < content)
                    rotateWithRightChild(node);

                else
                    doubleWithRightChild(node);
            }



    }
    //element == content
    else{
        node->element = node->element + content;
    }
    node->height = max(height(node->left), height(node->right)) + 1;

}

template <class T>
void AVLTree<T>::rotateWithLeftChild(AVLNode<T> *& k2){

    AVLNode<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) +1;
    k1->height = max(height(k1->left), k2->height) +1;
    k2 = k1;

}

template <class T>
void AVLTree<T>::rotateWithRightChild(AVLNode<T> *& k1){

    AVLNode<T>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k1 = k2;
}

template <class T>
void AVLTree<T>::doubleWithLeftChild(AVLNode<T> *& k3){

    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);

}

template <class T>
void AVLTree<T>::doubleWithRightChild(AVLNode<T> *& k1){

    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);

}

template <class T>
AVLNode<T>* AVLTree<T>::getRoot() {
    return root;
}

template <class T>
int AVLTree<T>::getElementCount(){

    return elementCount;

}

template <class T>
void AVLTree<T>::clearTree(){

    if(root != nullptr){
        delete root;
        root = nullptr;
    }
}

template <class T>
bool AVLTree<T>::isEmpty(){
    if(root == nullptr)
        return true;
    else
        return false;
}

template <class T>
std::ostream& AVLTree<T>::printTree(std::ostream& o,  AVLNode<T>* node) {

//    if (node != nullptr) {
//        printTree(o, node->left);
//        o << "\"" << node->element << "\",";
//        printTree(o, node->right);
//    }
//    return o;


    if(node == nullptr){

        o << "\nNULL" << endl;
    }


    else{

        o << node->element;
        printTree(o, node->left);
        printTree(o, node->right);

    }
    return o;

}


template <class T>
void AVLTree<T>::saveTree(ofstream& outputFile) {
    saveTree(outputFile, root);
}

template <class T>
void AVLTree<T>::saveTree(ofstream& outputFile, AVLNode<T>*& node) {
    if (node != nullptr) {
        outputFile << node->element << "NEW_ELEMENT\n"; //need NEW_ELEMENT?
        saveTree(outputFile, node->left);
        saveTree(outputFile, node->right);
    }
}

template <class U>
std::ostream& operator<<(std::ostream& o,  AVLTree<U>& tree)
{
    //"start" and 31 dashes
    o << "Start Tree" << endl;
    if(tree.getRoot() != nullptr)
        tree.printTree(o, tree.getRoot());
    else
        o << "NULL" << endl;
    //"end" and 33 dashes

    return o;
}

//destructor
template <class T>
AVLTree<T>::~AVLTree(){

    clearTree();

}

#endif // AVLTREE_H
