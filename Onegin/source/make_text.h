#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include "text.h"

#define REDASSERT(str) "\033[0;31m" #str "\033[0m"

Text FillText(const char* filename, ERRORS* error);
ERRORS OpenFile(Text* onegin, const char* filename);
ERRORS ReadBuffer(Text* onegin);
size_t FillLineArray(Text* onegin, ERRORS* error);

#endif // ONEGIN_H_INCLUDED
