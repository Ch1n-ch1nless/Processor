#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

#include "text.h"

#define REDASSERT(str) "\033[0;31m" #str "\033[0m"

Errors FillText(const char* filename, Text* onegin);
Errors OpenFile(Text* onegin, const char* filename);
Errors ReadBuffer(Text* onegin);
size_t FillLineArray(Text* onegin, Errors* error);

#endif // ONEGIN_H_INCLUDED
