#include <FlexLexer.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#include "compilateur.h"
#include "tokeniser.h"

using namespace std;

TOKEN current;

int rom_file;


FlexLexer* lexer = new yyFlexLexer; // This is the flex tokeniser
// tokens can be read using lexer->yylex()
// lexer->yylex() returns the type of the lexicon entry (see enum TOKEN in tokeniser.h)
// and lexer->YYText() returns the lexicon entry as a string

void Error(string s){
	cerr << "Ligne n°"<<lexer->lineno()<<", read : '"<<lexer->YYText()<<"'("<<current<<"), but ";
	cerr<< s << endl;
	exit(-1);
}

void writeOpcode(unsigned short opcode){
    unsigned char opcodeSplit[2];
    opcodeSplit[0] = opcode >> 8;
    opcodeSplit[1] = opcode & 0x00FF;

    write(rom_file,opcodeSplit,2);
}

void CLS(){
    writeOpcode(0x00E0);
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
        return -1;
    }
    if(argc < 3){
        cerr << "rom file destination is missing from the arguments" << endl;
        return -1;
    }
    
    int asm_file;
    asm_file = open(argv[1],O_RDONLY);
    close(0);
    dup(asm_file);
    close(asm_file);

    creat(argv[2],0777);
    rom_file = open(argv[2],O_RDWR);

    current=(TOKEN) lexer->yylex();
    processInstruction();

    if(current != FEOF) Error("unexpected characters at the end of program");
}