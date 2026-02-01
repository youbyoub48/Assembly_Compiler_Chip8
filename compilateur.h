#include <map>
#include <string>

typedef void (*func)();

void CLS();
void RET();
void SYS();

std::map<std::string,func> instructions = {
    {"CLS",&CLS},
    {"RET",&RET},
    {"SYS",&SYS},
};