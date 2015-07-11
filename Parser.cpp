#include "Parser.h"
//Constructor opens the input file/stream and gets ready to parse it
Parser::Parser(string file){
    input_file = file;
    fin.open(input_file.c_str());
    if(fin.fail()){
        cout << "Invalid file name." << endl;
    }
    //advance(); // "Advance" to the first command of the file
}
string Parser::getCurrentCommand(){
    return current_command;
}
//Are there more commands in the input?
bool Parser::hasMoreCommands(){
    return !fin.eof();
}
//Return valid command?
bool Parser::validCommand(){
    return valid_command;
}
// Finds the next line that does not begin with "//" and sets as current_command
void Parser::advance(){
    valid_command = false;
    string current_line;
    while(!valid_command && hasMoreCommands()){
        semicolon = equalSign = firstBlank = 0;
        getline(fin, current_line);
        //remove leading blanks
        current_line.erase(0, current_line.find_first_not_of(" \t\r\n"));
        //Remove trailing  Comment
        for(int i = 0; i < current_line.size(); i++){
            if(current_line.substr(i, 2).compare("//") == 0){
              current_line.erase(i, string::npos);
            }
        }
        //Remove trailing blanks if there are any
        if (current_line.find_first_of(" \t\r\n")!= string::npos)
            current_line.erase(current_line.find_first_of(" \t\r\n"), string::npos);
        
        if(!current_line.empty())valid_command = true;
    }
    if(valid_command){
        current_command = current_line;
        // Determine index of the semicolon, equal sign, and first blank space after command  
        while(current_command[equalSign]!= '=' && equalSign < current_command.size())
            equalSign++;      
        while(current_command[semicolon]!=';' && semicolon < current_command.size())
            semicolon++;        
        while(current_command[firstBlank] != ' ' && firstBlank < current_command.size())
            firstBlank++;
        
        if(firstBlank != string::npos)
        current_command.erase(firstBlank, string::npos);
    }
    
}
//Reset fin to begining of file 
void Parser::reset(){
    fin.clear();
    fin.seekg(0, ios::beg);
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
    
    if(commandType() == A_COMMAND)
        return current_command.substr(1, firstBlank-1); 
    else if (commandType() == L_COMMAND)
        return current_command.substr(1, firstBlank-2);
    
    else cout << "symbol() called on C_COMMAND" << endl;     
}
//returns the dest mnemonic in the current C_COMMAND 
string Parser::dest(){
    if(commandType() != C_COMMAND){
        cout << "dest() called on non-C_COMMAND " << endl;
    }
    return current_command.substr(0, equalSign);    
}
//returns the comp mnemonic in the current C_COMMAND 
string Parser::comp(){
    if(commandType() != C_COMMAND){
        cout << "comp() called on non-C_COMMAND " << endl;
    }
     
    if (equalSign >= current_command.size())
        return current_command.substr(0, semicolon);// no '=' found form "comp;jump"
    else if (semicolon >= current_command.size())            
        return current_command.substr(equalSign+1, firstBlank-1);//no ';'found form "dest=comp"    
    else                                                     
        return current_command.substr(equalSign+1, semicolon-1); // form dest=comp;jump
}
//returns the jump mnemonic in the current C_COMMAND 
string Parser::jump(){
    if(commandType() != C_COMMAND)
        cout << "jump() called on non-C_COMMAND " << endl;
    if (semicolon < current_command.size())
        return current_command.substr(semicolon+1, string::npos);
    else
        return "";
}