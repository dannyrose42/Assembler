#include "Coder.h"
Coder::Coder(){
   assembly_instruction = "";  
}
/*==========================================================================
*IN: HACK assembly destination mnemonic
*OUT: 3 bit HACK machine code corresponding to IN mnemonic
 * Mnemonic | d1 d2 d3
 * -------------------
 * null     | 0  0  0
 * M        | 0  0  1
 * D        | 0  1  0
 * MD       | 0  1  1
 * A        | 1  0  0
 * AM       | 1  0  1
 * AD       | 1  1  0
 * AMD      | 1  1  1
 */
string Coder::dest(string destMnemonic){
    if (destMnemonic.compare("null")==0)
        return "000";
    else if (destMnemonic.compare("M")==0)
        return "001";
    else if (destMnemonic.compare("D")==0)
        return "010";
    else if (destMnemonic.compare("MD")==0)
        return "011";
    else if (destMnemonic.compare("A")==0)
        return "100";
    else if (destMnemonic.compare("AM")==0)
        return "101";
    else if (destMnemonic.compare("AD")==0)
        return "110";
    else if (destMnemonic.compare("AMD")==0)
        return "111";
    else 
        return "eee";
}
/*==========================================================================
*IN: HACK assembly comp mnemonic
*OUT: 3 bit HACK machine code corresponding to IN mnemonic
 * Mnemonic | a  c1 c2 c3 c4 c5 c6 
 * -------------------------------
 * 0        | 0  1  0  1  0  1  0
 * 1        | 0  1  1  1  1  1  1
 * -1       | 0  1  1  1  0  1  0
 * D        | 0  0  0  1  1  0  0
 * A        | 0  1  1  0  0  0  0
 * M        | 1  1  1  0  0  0  0
 * !D       | 0  0  0  1  1  0  1
 * !A       | 0  1  1  0  0  0  1
 * !M       | 1  1  1  0  0  0  1
 * -D       | 0  0  0  1  1  1  1
 * -A       | 0  1  1  0  0  1  1
 * -M       | 1  1  1  0  0  1  1
 * D+1      | 0  0  1  1  1  1  1
 * A+1      | 0  1  1  0  1  1  1
 * M+1      | 1  1  1  0  1  1  1
 * D-1      | 0  0  0  1  1  1  0
 * A-1      | 0  1  1  0  0  1  0
 * M-1      | 1  1  1  0  0  1  0
 * D+A      | 0  0  0  0  0  1  0
 * D+M      | 1  0  0  0  0  1  0
 * D-A      | 0  0  1  0  0  1  1
 * D-M      | 1  0  1  0  0  1  1
 * A-D      | 0  0  0  0  1  1  1
 * M-D      | 1  0  0  0  1  1  1
 * D&A      | 0  0  0  0  0  0  0
 * D&M      | 1  0  0  0  0  0  0
 * D|A      | 0  0  1  0  1  0  1
 * D|M      | 1  0  1  0  1  0  1
 */
string Coder::comp(string compMnemonic){    
    if (compMnemonic.compare("0")==0)
        return "0101010";
    else if (compMnemonic.compare("1")==0)
        return "0111111";
    else if (compMnemonic.compare("-1")==0)
        return "0111010";
    else if (compMnemonic.compare("D")==0)
        return "0001100";
    else if (compMnemonic.compare("A")==0)
        return "0110000";
    else if (compMnemonic.compare("M")==0)
        return "1110000";
    else if (compMnemonic.compare("!D")==0)
        return "0001101";
    else if (compMnemonic.compare("!A")==0)
        return "0110001";
    else if (compMnemonic.compare("!M")==0)
        return "1110001";
    else if (compMnemonic.compare("!D")==0)
        return "0001111";
    else if (compMnemonic.compare("-A")==0)
        return "0110011";
    else if (compMnemonic.compare("-M")==0)
        return "1110011";
    else if (compMnemonic.compare("D+1")==0)
        return "0011111";
    else if (compMnemonic.compare("A+1")==0)
        return "0110111";
    else if (compMnemonic.compare("M+1")==0)
        return "1110111";
    else if (compMnemonic.compare("A-1")==0)
        return "0110010";
    else if (compMnemonic.compare("M-1")==0)
        return "1110010";
    else if (compMnemonic.compare("D+A")==0)
        return "0000010";
    else if (compMnemonic.compare("D+M")==0)
        return "1000010";
    else if (compMnemonic.compare("D-A")==0)
        return "0010011";
    else if (compMnemonic.compare("D-M")==0)
        return "1010011";
    else if (compMnemonic.compare("A-D")==0)
        return "0000111";
    else if (compMnemonic.compare("M-D")==0)
        return "1000111";
    else if (compMnemonic.compare("D&A")==0)
        return "0000000";
    else if (compMnemonic.compare("D&M")==0)
        return "1000000";
    else if (compMnemonic.compare("D|A")==0)
        return "0010101";
    else if (compMnemonic.compare("D|M")==0)
        return "1010101";
    else
        return "eeeeeee";
}   
/*==========================================================================
*IN: HACK assembly Jump mnemonic
*OUT: 3 bit HACK machine code corresponding to IN mnemonic
 * Mnemonic | j1 j2 j3
 * -------------------
 * null     | 0  0  0
 * JGT      | 0  0  1
 * JEQ      | 0  1  0
 * JGE      | 0  1  1
 * JLT      | 1  0  0
 * JNE      | 1  0  1
 * JLE      | 1  1  0
 * JMP      | 1  1  1
 */
string Coder::jump(string jumpMnemonic){    
    if (jumpMnemonic.compare("null")==0)
        return "000";
    else if (jumpMnemonic.compare("JGT")==0)
        return "001";
    else if (jumpMnemonic.compare("JEQ")==0)
        return "010";
    else if (jumpMnemonic.compare("JGE")==0)
        return "011";
    else if (jumpMnemonic.compare("JLT")==0)
        return "100";
    else if (jumpMnemonic.compare("JNE")==0)
        return "101";
    else if (jumpMnemonic.compare("JLE")==0)
        return "110";
    else if (jumpMnemonic.compare("JMP")==0)
        return "111";
}
