#include "userinterface.h"
#include "indexhandler.h"
#include <cstring>
#include <iostream>
#include <limits>
using namespace std;

UserInterface::UserInterface() {
    returnToModeChoice = true;
    indexHandler = nullptr;
}

UserInterface::UserInterface(int& argc, char* argv[]) {
    returnToModeChoice = true;
    //pass command line args to load index at start of program
    indexHandler = new IndexHandler(argc, argv);
}

void UserInterface::runProgram() {
    int modeChoice = 0;
    cout << "\n*************Mode Choice*************\n\n"
         << "Please choose a mode:\n\n1. Interactive\n2. Maintenance\n\nChoice: ";
    while (modeChoice == 0) {
        checkInput(modeChoice);
        //if user chooses interactive
        if (modeChoice == 1) {
            runInteractiveMode();
        }
        //if user chooses maintenance
        else if (modeChoice == 2) {
            runMaintenanceMode();
        }
        //if user enters int other than 1 or 2
        else {
            errorMessage(modeChoice);
        }
        if (returnToModeChoice) {
            cout << "\n*************Mode Choice*************\n\n"
                 << "Please choose a mode:\n\n1. Interactive\n2. Maintenance\n\nChoice: ";
            modeChoice = 0;
        }
        else {
            break;
        }
    }
    indexHandler->saveIndex();
    cout << "\tIndex successfully saved\n" << endl;
}

void UserInterface::checkInput(int& choice) {
    //check for bad input (not int)
    while(!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again: ";
    }
}

void UserInterface::errorMessage(int& choice) {
    choice = 0;
    cout << "Invalid input. Try again: ";
}

/*
 *
 *
 *          Interactive Mode
 *
 *
 */

void UserInterface::runInteractiveMode() {
    chooseIndexType();
    chooseMenuOption_I();
}

void UserInterface::chooseIndexType() {
    cout << "\n*************Interactive Mode*************\n\nPlease choose the index type:"
         << "\n\n1. AVL Tree\n2. Hash Table\n\nChoice: ";
    int choice = 0;
    while (choice == 0) {
        checkInput(choice);
        //if choose AVL Tree
        if (choice == 1) {
            char type = 'a';
            indexHandler->setIndexType(type);
            break;
        }
        //if choose Hash Table
        if (choice == 2) {
            char type = 'h';
            indexHandler->setIndexType(type);
            break;
        }
        //if enter int other than 1 or 2
        else {
            errorMessage(choice);
        }
    }
}

void UserInterface::chooseMenuOption_I() {
    displayMenuOptions_I();
    int choice = 0;
    while (choice == 0) {
        checkInput(choice);
        //if choose to enter search query
        if (choice == 1) {
            readQuery();
            choice = 0;
            displayMenuOptions_I();
        }
        //if choose to show search engine statistics
        else if (choice == 2) {
            showStatistics();
            choice = 0;
            displayMenuOptions_I();
        }
        //if choose to return to mode choice
        else if (choice == 3) {
            break;
        }
        //if choose to exit program
        else if (choice == 4) {
            cout << "Saving index..." << endl;
            returnToModeChoice = false;
            break;
        }
        //if enter int other than 1 or 2 or 3 or 4
        else {
            errorMessage(choice);
        }
    }
}

void UserInterface::displayMenuOptions_I() {
    cout << "\nPlease choose one of the following:"
         << "\n\n1. Enter Search Query\n2. Show Search Engine Statistics"
         << "\n3. Return to Choose Mode\n4. Exit Program\n\nChoice: ";
}

void UserInterface::readQuery() {
    string query;
    cout << "\nPlease enter search query: ";
    //read line of user input
    cin.ignore();
    getline(cin, query);
    indexHandler->processQuery(query);
}

void UserInterface::showStatistics() {
    int numWords = indexHandler->getNumWords();
    int numQs = indexHandler->getNumQuestions();
    cout << "\nSearch Engine Statistics:";
    cout << "\n\t" << numQs << " Questions Indexed\n\t";
    cout << numWords << " Words Indexed\n" << endl;
}

/*
 *
 *
 *          Maintenance Mode
 *
 *
 */

void UserInterface::runMaintenanceMode() {
    chooseMenuOption_M();
}

void UserInterface::chooseMenuOption_M() {
    displayMenuOptions_M();
    int choice = 0;
    while (choice == 0) {
        checkInput(choice);
        //if choose to clear index
        if (choice == 1) {
            indexHandler->clearIndex();
            cout << "\tIndex successfully cleared\n" << endl;
            choice = 0;
            displayMenuOptions_M();
        }
        //if choose to provide CSV file location
        else if (choice == 2) {
            readDocLocation();
            choice = 0;
            displayMenuOptions_M();
        }
        //if choose to return to mode choice
        else if (choice == 3) {
            break;
        }
        //if choose to exit program
        else if (choice == 4) {
            cout << "Saving index..." << endl;
            returnToModeChoice = false;
            break;
        }
        //if enter int other than 1 or 2
        else {
            errorMessage(choice);
        }
    }
}

void UserInterface::displayMenuOptions_M() {
    cout << "\n*************Maintenance Mode*************\n\nPlease choose one of the following:"
         << "\n\n1. Clear Index\n2. Provide CSV File Location"
         << "\n3. Return to Choose Mode\n4. Exit Program\n\nChoice: ";
}

void UserInterface::readDocLocation() {
    string tempPath;
    cout << "Please enter the path to the CSV file: ";
    //pass path to indexHandler to docParser
    cin >> tempPath;
    char *path = new char[tempPath.length() + 1];
    strcpy(path, tempPath.c_str());
    indexHandler->passDocPath(path);
    delete [] path;
    cout << "\tCSV file successfully parsed" << endl;
}
