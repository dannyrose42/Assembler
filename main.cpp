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
    string inputFile = "add_nc.asm";
    char selection;
    string dest, comp, jump, machineComp, machineDest, machineJump, command;
    bool quit = false;
//    cout << "Enter Assembly File Name:" << endl;
//    getline(cin, inputFile);
    Coder Coder;
    Parser Parser(inputFile);
    while(!quit){
        cout << "Enter selection:" << endl;
        cout << "a: Advance" << endl;
        cout << "q: Quit" << endl;
        
        cin >> selection;
        
        if (selection == 'a'){
            
        }
        else if(selection == 'q')quit=true;
        
    }

}



