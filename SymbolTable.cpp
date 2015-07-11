#include "SymbolTable.h"
//Initialize pre-defined symbols
SymbolTable::SymbolTable(){
    hashTable.emplace("SP", 0);
    hashTable.emplace("LCL", 1);
    hashTable.emplace("ARG", 2);
    hashTable.emplace("THIS", 3);
    hashTable.emplace("THAT", 4);

    hashTable.emplace("R0", 0);
    hashTable.emplace("R1", 1);
    hashTable.emplace("R2", 2);
    hashTable.emplace("R3", 3);
    hashTable.emplace("R4", 4);
    hashTable.emplace("R5", 5);
    hashTable.emplace("R6", 6);
    hashTable.emplace("R7", 7);
    hashTable.emplace("R8", 8);
    hashTable.emplace("R9", 9);
    hashTable.emplace("R10", 10);
    hashTable.emplace("R11", 11);
    hashTable.emplace("R12", 12);
    hashTable.emplace("R13", 13);
    hashTable.emplace("R14", 14);
    hashTable.emplace("R15", 15);
    
    hashTable.emplace("SCREEN", 16384);
    hashTable.emplace("KBD", 24576);   
}
void SymbolTable::addEntry(string symbol, int address){
    hashTable.emplace(symbol, address);
}
//Returns true if the hashtable contains the symbol
bool SymbolTable::contains(string symbol){
    return hashTable.count(symbol);
}
//Returns the address associated with the symbol
int SymbolTable::getAddress(string symbol){
    if (contains(symbol))
        return hashTable[symbol];
    else
        cout << "Error: getAddress called on invalid key" << endl;
        return -1; 
}

