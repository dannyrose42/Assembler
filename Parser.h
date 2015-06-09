/* 
 * File:   Parser.h
 * Author: Daniel Rose
 *
 * Reads an assembly language command, parses it, and provides convenient 
 * access o the command's components (fields and symbols). In addition, removes
 * all white spaces comments
 */
#ifndef __PARSER_H__
#define	__PARSER_H__
#include "Utility.h"
class Parser
{
public:
    Parser();
    Parser(string input_file);
    string getCurrentCommand();
    bool hasMoreCommands();
    void advance();
    COMMAND_TYPE commandType();

    string symbol();
    string dest();
    string comp();
    string jump(); 


protected:
    fstream fin;
    string current_command;      
};
#endif	/* PARSER_H */

