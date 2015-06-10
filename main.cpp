/* 
 * File:   main.cpp
 * Author: Daniel ROse
 *
 * Created on June 6, 2015, 8:35 AM
 */

#include "Utility.h"
#include "Coder.h"
#include "Parser.h"

int main(int argc, char** argv) {
    string inputFile = "add.asm";
    char selection;
    string dest, comp, jump, machineComp, machineDest, command;
    bool quit = false;
//    cout << "Enter Assembly File Name:" << endl;
//    getline(cin, inputFile);
    Coder Coder;
    Parser Parser(inputFile);   
    cout << "command:" << Parser.getCurrentCommand() << endl;
    switch(Parser.commandType()){
        case C_COMMAND:
            
            comp = Parser.comp();
            machineComp = Coder.comp(comp);
            cout << "comp: " << comp << " - " << machineComp << endl;
            
            dest = Parser.dest();
            machineDest = Coder.dest(dest);
            cout << "dest: " << dest << " - " << machineDest << endl;
            
            
            break;
        case A_COMMAND:
            cout << "symbol: " << Parser.symbol() << endl;
    }
}



