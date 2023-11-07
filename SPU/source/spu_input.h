#ifndef SPU_INPUT_H_INCLUDED
#define SPU_INPUT_H_INCLUDED

#include "spu.h"
#include "sys/stat.h"
#include <stdlib.h>

error_t OpenFile(FILE** file_pointer, const char* file_name, const char* mode);

error_t CountBufferSize(Processor* clm, const char* file_name);

error_t ReadArrayOfCommands(FILE* file_pointer, Processor* clm);

#endif // SPU_INPUT_H_INCLUDED
