
#include "userinterface.h"
#include "HashTable.h"
#include <iostream>

#include <stdio.h>

#include "documentParser.h"
#include "indexer.h"

using namespace std;

int main(int argc, char *argv[]) {
    UserInterface project(argc, argv);
    project.runProgram();
}
