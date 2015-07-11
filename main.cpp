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
        switch(Parser.commandType()){
            case A_COMMAND:
                labelAddr++;
                break; 
            case C_COMMAND:
                labelAddr++;
                break;
            case L_COMMAND:
                SymbolTable.addEntry(Parser.symbol(), labelAddr);
                break; 
        }     
    }
    //reset fstream to beginning of file for next pass
    Parser.reset(); 

    //Second Pass: Adds program's variables to symbol table and completes translation    
    variableAddr = 16;
    output.open(outputFile.c_str());
    if (output.fail()) cout << "Failed to initialize output" << endl;
    while(Parser.hasMoreCommands()){
        Parser.advance();
        if(Parser.validCommand()){
            switch (Parser.commandType()){
                case C_COMMAND:
                    //Build C_COMMAND machine code word
                    machineComp = Coder.comp(Parser.comp());
                    machineDest = Coder.dest(Parser.dest());
                    machineJump = Coder.jump(Parser.jump());
                    // Write C_command machine code word to output
                    output << "111" << machineComp << machineDest << machineJump << endl;
                    break;
                case A_COMMAND:;
                    //Determines if @ instruction is decimal or label:
                    if(Parser.symbol().find_first_not_of("0123456789") == string::npos){
                    //Xxx is a decimal number
                        output << Coder.dec(Parser.symbol()) << endl;}
                    else{//Xxx is variable or label
                         // Look for symbol in symbol table
                        if(SymbolTable.contains((Parser.symbol()))){
                            //Found in Symbol Table, build machine code word and write to output
                            output << Coder.dec(SymbolTable.getAddress(Parser.symbol())) << endl;
                        }
                        //Symbol not found in SymbolTable: Must be new variable, add to symbol table,
                        //build machine code word and write to output 
                        else{
                            SymbolTable.addEntry(Parser.symbol(), variableAddr);
                            variableAddr++;
                            output << Coder.dec(SymbolTable.getAddress(Parser.symbol())) << endl;
                        }
                    }
                    break;
            }      
        }  
    }
    output.close();
}



