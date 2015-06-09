#include "Parser.h"
//Constructor opens the input file/stream and gets ready to parse it
Parser::Parser(string input_file){
    fin.open(input_file.c_str());
    if(fin.fail()){
        cout << "Invalid file name." << endl;
    }
    advance(); // "Advance" to the first command of the file
}
string Parser::getCurrentCommand(){
    return current_command;
}
//Are there more commands in the input?
bool Parser::hasMoreCommands(){
    return !fin.eof();      
}
// Finds the next line that does not begin with "//" and sets as current_command
void Parser::advance(){
    bool valid_command = false;
    string current_line;
    while(!valid_command && hasMoreCommands()){
        getline(fin, current_line);
        //remove leading blanks
        current_line.erase(0, current_line.find_first_not_of(" \t\r\n"));
        if(current_line.substr(0, 2).compare("//") != 0){
          valid_command = true;  
        }
    }
    if(valid_command){
        current_command = current_line;
        return;
    }
    else cout << "Could not advance: reached end of file" << endl;    
}
/* Returns the type of the current command.
 * A_COMMAND: for @Xxx where Xxx is either a symbol or a decimal number
 * 
 * L_COMMAND: (actually pseudo-command) for (Xxx) where Xxx is a symbol
 * 
 * C_COMMAND: for dest=comp;jump
 */
COMMAND_TYPE Parser::commandType(){
   switch (current_command[0]){
        case '@':
            return A_COMMAND;
            break;
        case '(':
            return L_COMMAND;
            break;
        default:
            return C_COMMAND;
            break;               

   }
}
/*Returns the symbol or decimal Xxx of the current command @Xxx or (Xxx). 
 * Should be called only when type is A_COMMAND or L_COMMAND.
 */
string Parser::symbol(){
    if(commandType() == C_COMMAND){
        cout << "symbol() called on C_COMMAND" << endl;
    }
    return current_command.substr(1,3);
}
/*returns the dest mnemonic in the current C_COMMAND (8 possibilities). Should
 * be called only when commandType() is C_COMMAND>
 */
string Parser::dest(){
    if(commandType() != C_COMMAND){
        cout << "dest() called on non-C_COMMAND " << endl;
    }
    int i = 0;
    
    while(current_command[i]!= '=' && i < current_command.size()){
        i++;
    }
    return current_command.substr(0, i-1);    
}
string Parser::comp(){
    if(commandType() != C_COMMAND){
        cout << "comp() called on non-C_COMMAND " << endl;
    }
    int i = 0;
    
    while(current_command[i]!= '=' && i < current_command.size()){
        i++;
    }
    int j = 0;
    while(current_command[j]!=';' && j < current_command.size()){
        j++;
    }
    
    if (i > current_command.size())
        return current_command.substr(0, j-1);// no '=' found form "comp;jump
    else
        return current_command.substr(i, j-1);//'=' found form "dest=comp;jump"    
}                                             //            or "dest=comp"
string Parser::jump(){
    if(commandType() != C_COMMAND){
        cout << "jump() called on non-C_COMMAND " << endl;
    }
    int i = 0;
    
    while(current_command[i]!= ';' && i < current_command.size()){
        i++;
    }
    return current_command.substr(i, current_command.size()-1);  
    
}