#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "indexhandler.h"

class UserInterface
{
public:
    UserInterface();
    UserInterface(int&, char* argv[]);
    void runProgram();
private:
    //member functions
    void checkInput(int&);
    void errorMessage(int&);

    //interactive mode
    void runInteractiveMode();
    void chooseIndexType();
    void chooseMenuOption_I();
    void displayMenuOptions_I();
    void readQuery();
    void showStatistics();

    //maintenance mode
    void runMaintenanceMode();
    void chooseMenuOption_M();
    void displayMenuOptions_M();
    void readDocLocation();

    //data members
    IndexHandler* indexHandler;
    bool returnToModeChoice;
};

#endif // USERINTERFACE_H
