%{
// This is our Lexical tokeniser 
// It should be compiled into cpp with :
// flex++ -d -otokeniser.cpp tokeniser.l 
// And then compiled into object with
// g++ -c tokeniser.cpp
// tokens can be read using lexer->yylex()
// lexer->yylex() returns the type of the lexicon entry (see enum TOKEN in tokeniser.h)
// and lexer->YYText() returns the lexicon entry as a string

#include "tokeniser.h"
#include <iostream>

using namespace std;

%}

%option noyywrap
%option c++
%option yylineno

ws      [ \t\n\r]+
alpha   [A-Za-z]
digit   [0-9]
number  {digit}+
label	{alpha}({alpha}|{digit})*
address 0x({alpha}|{digit})*
unknown [^\"A-Za-z0-9 \n\r\t\(\)\<\>\=\!\%\&\|\}\-\;\.]+
instruction ("CLS"|"RET"|"SYS"|"JP"|"CALL"|"SE"|"SNE"|"LD"|"ADD"|"OR"|"AND"|"XOR"|"SUB"|"SHR"|"SUBN"|"SHL"|"RND"|"DRW"|"SKP"|"SKNP")

%%

{instruction}	return INSTRUCTION;
{address}	return ADDRESS;
{number}	return NUMBER;
{label}		return LABEL;
":"		return COLON;
"["		return RBRACKET;
"]"		return LBRACKET;
","		return COMMA;
"."		return DOT;
<<EOF>>		return FEOF;
{ws}    {/* skip blanks and tabs */};
"/*"    { /* Skip comments between '(*' and '*)' */
		int c;
		while((c = yyinput()) != 0){
     			if(c == '*'){
     	    			if((c = yyinput()) == '/')
    	        			break;
    	     			else
  	          			unput(c);
  	   		}	
		}
	};

{unknown}	return UNKNOWN;

%%

