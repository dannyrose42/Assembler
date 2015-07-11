/* 
 * File:   SymbolTable.h
 * Author: Danny
 *
 * Created on June 24, 2015, 4:40 PM
 */

#ifndef __SYMBOLTABLE_H__
#define	__SYMBOLTABLE_H__
#include "Utility.h"
#include <unordered_map>
class SymbolTable 
{
public:
    SymbolTable();
    void addEntry(string symbol, int address);
    bool contains(string symbol);
    int getAddress(string symbol);
protected:
    unordered_map<string, int> hashTable;   
};
#endif	/* SYMBOLTABLE_H */

