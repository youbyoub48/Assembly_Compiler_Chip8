#include <map>
#include <string>

typedef void (*func)();

void CLS();

std::map<std::string,func> instructions = {
    {"CLS",&CLS}
};