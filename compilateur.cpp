#include <FlexLexer.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#include "compilateur.h"
#include "tokeniser.h"

using namespace std;

TOKEN current;


FlexLexer* lexer = new yyFlexLexer; // This is the flex tokeniser
// tokens can be read using lexer->yylex()
// lexer->yylex() returns the type of the lexicon entry (see enum TOKEN in tokeniser.h)
// and lexer->YYText() returns the lexicon entry as a string

void Error(string s){
	cerr << "Ligne n°"<<lexer->lineno()<<", read : '"<<lexer->YYText()<<"'("<<current<<"), but ";
	cerr<< s << endl;
	exit(-1);
}

void CLS(){
    cout << "erase" << endl;
}

void processInstruction(){
    if(current != INSTRUCTION) Error("expected instruction");

    instructions.at(lexer->YYText())();

    current=(TOKEN) lexer->yylex();
    if(current == INSTRUCTION) processInstruction();
}

int main(int argc, char **argv){
    if(argc < 2){
        cerr << "assembly file is missing from the arguments" << endl;
        return 1;
    }
    
    int fich;
    fich = open(argv[1],O_RDWR);
    close(0);
    dup(fich);
    close(fich);

    current=(TOKEN) lexer->yylex();
    processInstruction();

    if(current != FEOF) Error("unexpected characters at the end of program");
}