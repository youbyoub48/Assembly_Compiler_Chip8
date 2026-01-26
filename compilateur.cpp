#include <FlexLexer.h>
#include <iostream>
#include "tokeniser.h"
#include <fcntl.h>
#include <unistd.h>

using namespace std;

TOKEN current;				// Current token


FlexLexer* lexer = new yyFlexLexer; // This is the flex tokeniser
// tokens can be read using lexer->yylex()
// lexer->yylex() returns the type of the lexicon entry (see enum TOKEN in tokeniser.h)
// and lexer->YYText() returns the lexicon entry as a string

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
    cout << lexer->YYText() << endl;
    cout << current << endl;
}