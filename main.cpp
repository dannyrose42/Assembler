/* 
 * File:   main.cpp
 * Author: Daniel ROse
 *
 * Created on June 6, 2015, 8:35 AM
 */

#include "Utility.h"
#include "Coder.h"
#include "Parser.h"
#include "SymbolTable.h"

int main(int argc, char** argv) {
    string inputFile, outputFile = "";
    char selection;
    bool quit = false;
    int labelAddr, variableAddr;
    ofstream output;
    string dest, 
           comp,
           jump, 
           machineComp, 
           machineDest, 
           machineJump, 
           command;
    
    cout << "Enter Assembly File Name:" << endl;
    getline(cin, inputFile);
    outputFile = inputFile;
    //Replace ".asm" extention with ".HACK"
    outputFile.erase(outputFile.size()-4, 4);
    outputFile.append(".hack");
   
    Coder Coder;
    SymbolTable SymbolTable;
    Parser Parser(inputFile);
    
    //First Pass: Adds all labels to the symbol table
    labelAddr = 0;
    while(Parser.hasMoreCommands()){
        Parser.advance();
        cout << "CommandType:" << Parser.getCurrentCommand() << endl;
        cout << "Command:" << Parser.getCurrentCommand() << endl;
        cout << "LabeAddr:" << labelAddr << endl << endl;
        switch(Parser.commandType()){
            case A_COMMAND:
                labelAddr++;
                break; 
            case C_COMMAND:
                labelAddr++;
                break;
            case L_COMMAND:
                SymbolTable.addEntry(Parser.symbol(), labelAddr);
                cout << "adding symbol table:" << Parser.symbol() << endl; 
                break; 
        }     
    }
    //reset fstream to begining of file for next pass
    Parser.reset(); 

    //Second Pass: Adds program's variables to symbol table and completes translation    
    variableAddr = 16;
    output.open(outputFile.c_str());
    if (output.fail()) cout << "Failed to initialize output" << endl;
    while(Parser.hasMoreCommands()){
        Parser.advance();
        
//        cout << "commandType:" << Parser.commandType() << endl;
//        cout << "command:" << Parser.getCurrentCommand() << '.' << endl;
//        cout << "size:" << Parser.getCurrentCommand().size() << endl;
//        cout << "semicolon:" << Parser.semicolon << endl;
//        cout << "equalSign:" << Parser.equalSign << endl;
//        cout << "firstBlank:" << Parser.firstBlank << endl; 

        switch (Parser.commandType()){
            case C_COMMAND:
                machineComp = Coder.comp(Parser.comp());
                machineDest = Coder.dest(Parser.dest());
                machineJump = Coder.jump(Parser.jump());                 
                output << "111" << machineComp << machineDest << machineJump << endl;
                
//                cout << "comp:" << Parser.comp() << "." << endl;
//                cout << "dest:" << Parser.dest() << "." << endl;
//                cout << "jump:" << Parser.jump() << "." << endl;
//                cout << "MachineJump:" << machineJump << endl;
//                cout << "MachineDest:" << machineDest << endl;
//                cout << "MachineComp:" << machineComp << endl << endl;
                 
                break;
            case A_COMMAND:
                cout << "symbol:" << Parser.symbol() << "." << endl;
                //Determines if @ instruction is decimal or label:
                if(Parser.symbol().find_first_not_of("0123456789") == string::npos){
                //Xxx is a decimal number
                    cout << "Symbol is decimal:" << Coder.dec(Parser.symbol()) << endl << endl;
                    output << Parser.symbol() << endl;}
                else{//Xxx is variable or label
                     // Look for symbol in symbol table
                    if(SymbolTable.contains((Parser.symbol()))){
                        cout << "In Table:" << Parser.symbol() << endl << endl;
                        output << Coder.dec(SymbolTable.getAddress(Parser.symbol())) << endl;
                    }
                    //Symbol not found in SymbolTable: Must be new variable, add to symbol table
                    else{
                        cout << "Adding variable to table:" << Parser.symbol() << "addr:" << variableAddr<< endl << endl;
                        SymbolTable.addEntry(Parser.symbol(), variableAddr);
                        variableAddr++;
                        output << Coder.dec(SymbolTable.getAddress(Parser.symbol())) << endl;
                    }
                }                
        }      
    }
    output.close();
}



