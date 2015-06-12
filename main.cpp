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
    string inputFile = "test.asm";
    char selection;
    bool quit = false;
    string dest, 
           comp,
           jump, 
           machineComp, 
           machineDest, 
           machineJump, 
           command;
    
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
            Parser.advance();
            if(Parser.commandType() == A_COMMAND){
                cout << "Decimal: " << Parser.getCurrentCommand() << endl;
                cout << Coder.dec(Parser.symbol()) <<  endl;
            }
            else {
                cout << "Command: " << Parser.getCurrentCommand() << endl;
                machineComp = Coder.comp(Parser.comp());
                machineDest = Coder.dest(Parser.dest());
                machineJump = Coder.jump(Parser.jump());
                cout << "Comp: " << Parser.comp() << " - " << machineComp << endl;
                cout << "Dest: " << Parser.dest() << " - " << machineDest << endl; 
                cout << "Jump: " << Parser.jump() << " - " << machineJump << endl;
                cout << "111" << machineComp << machineDest << machineJump << endl;
            }
        } else if(selection == 'q')quit=true;       
    }

}



