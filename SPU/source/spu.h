#ifndef SPU_H_INCLUDED
#define SPU_H_INCLUDED

#include "../../Stack/source/stack.h"

#include "../../Common_files/registers.h"

#include <TXLib.h>

#define CHECK_PROC_ERR(error, proc) error = ProcessorVerify(proc);                                    \
                                    if (error != NO_ERR)                                              \
                                    {                                                                 \
                                        ProcessorError(proc, error, __FILE__, __FUNCTION__, __LINE__);\
                                    }

#define PRINT_PROCESSOR(proc) ProcessorDump((proc), #proc, __FILE__, __FUNCTION__, __LINE__);

const size_t MAX_SIZE_OF_RAM    = 0x40000;
const size_t MAX_LEN_OF_STR     = 0x200;
const size_t MAX_SIZE_OF_VM     = 0x10000;
const size_t MAX_SIZE_OF_VM_STR = 0x100;
const size_t BEGIN_OF_VM        = 0x30000;

struct Processor
{
    Stack   stk;
    Stack   call_stk;
    elem_t* reg_array;
    int*    cmd_array;
    size_t  buf_size;
    elem_t* ram;
};

error_t ProcessorCtor(Processor* proc);
error_t ProcessorDtor(Processor* proc);

error_t ProcessorStkPush(Processor* proc, elem_t new_value);
error_t ProcessorStkPop(Processor* proc, elem_t* ret_value);

error_t ProcessorRegPush(Processor* proc, size_t index);
error_t ProcessorRegPop(Processor* proc, size_t index);

error_t ProcessorVerify(Processor* proc);
void    ProcessorError(Processor* proc, error_t error, const char* file, const char* function,
                                                                        const int line);

void    ProcessorDump(Processor* spu, const char* spu_name, const char* file,
                               const char* function, const int   line);

#endif // SPU_H_INCLUDED
