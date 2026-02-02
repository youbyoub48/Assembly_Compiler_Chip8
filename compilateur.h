#include <map>
#include <string>

#define MAXADDRESS 4095

typedef void (*func)();

void CLS();
void RET();
void SYS();
void JP();
void CALL();

std::map<std::string,func> instructions = {
    {"CLS",&CLS},
    {"RET",&RET},
    {"SYS",&SYS},
    {"JP",&JP},
    {"CALL",&CALL},
};