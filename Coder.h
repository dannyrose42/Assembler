/* 
 * File:   Coder.h
 * Author: Daniel Rose
 *
 * Translates HACK assembly language mnemonics into binary codes
 */
#ifndef __CODER_H__
#define	__CODER_H__
#include "Utility.h"
class Coder
{
public:
    Coder();
    string dest(string destMnemonic);
    string comp(string compMnemonic);
    string jump(string jumpMnemonic);
    string dec(string decimal);
};      
#endif	/* CODER_H */