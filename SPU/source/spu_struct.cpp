#include "spu_struct.h"

error_t ProcessorCtor(Processor* proc)
{
    assert(proc);

    error_t error = NO_ERR;

    error |= STACK_CTOR(&(proc->stk));

    error |= STACK_CTOR(&(proc->call_stk));

    proc->reg_array = (elem_t*) calloc(REGISTER_COUNT, sizeof(elem_t));
    if (proc->reg_array == nullptr)
    {
        error |= MEM_ALLOC_ERR;
    }

    proc->ram = (elem_t*) calloc(MAX_SIZE_OF_RAM, sizeof(elem_t));
    if (proc->ram == nullptr)
    {
        error |= MEM_ALLOC_ERR;
    }

    return error;
}

error_t ProcessorDtor(Processor* proc)
{
    assert(proc);

    error_t error = NO_ERR;

    error |= StackDtor(&(proc->stk));

    error |= StackDtor(&(proc->call_stk));

    free(proc->reg_array);
    proc->reg_array = nullptr;

    free(proc->cmd_array);
    proc->cmd_array = nullptr;

    free(proc->ram);
    proc->ram = nullptr;

    proc->buf_size = 0;

    return error;
}

error_t ProcessorStkPush(Processor* proc, elem_t new_value)
{
    assert(proc);

    error_t error = NO_ERR;

    error = StackPush(&(proc->stk), new_value);

    return error;
}

error_t ProcessorStkPop(Processor* proc, elem_t* ret_value)
{
    assert(proc);

    error_t error = NO_ERR;

    error = StackPop(&(proc->stk), ret_value);

    return error;
}

error_t ProcessorRegPush(Processor* proc, size_t index)
{
    assert(proc);

    error_t error = NO_ERR;

    elem_t new_value = POISON_VALUE;

    error = StackPop(&(proc->stk), &new_value);

    proc->reg_array[index] = new_value;

    return error;
}

error_t ProcessorRegPop(Processor* proc, size_t index)
{
    assert(proc);

    error_t error = NO_ERR;

    elem_t ret_value = proc->reg_array[index];

    error = StackPush(&(proc->stk), ret_value);

    return error;
}

error_t ProcessorVerify(Processor* proc)
{
    error_t error = StackVerify(&(proc->stk));

    if (proc->reg_array == nullptr)
    {
        error |= REG_ARRAY_NULLPTR_ERR;
    }

    if (proc->cmd_array == nullptr)
    {
        error |= CMD_ARRAY_NULLPTR_ERR;
    }

    return error;
}

void ProcessorError(Processor* proc, error_t error, const char* file, const char* function, const int line)
{
    PRINT_STK_ERROR(&(proc->stk), error);

    PRINT_STK_ERROR(&(proc->call_stk), error);

    FILE* output = fopen("error.log", "a");
    if (output == nullptr)
    {
        output = stderr;
    }

    switch(error)
    {
        case(REG_ARRAY_NULLPTR_ERR):
            fprintf(output, "Error! Pointer to array of registers is NULL!\n");
            break;

        case(CMD_ARRAY_NULLPTR_ERR):
            fprintf(output, "Error! Pointer to array of commands is NULL!\n");
            break;

        default:
            break;
    }
}

void ProcessorDump(Processor* proc, const char* spu_name, const char* file,
                               const char* function, const int   line)
{
    printf("Processor \"%s\": [%p]\n", spu_name, proc);
    printf("called from file: %s(%d) in function: %s\n{\n", file, line, function);

    printf("==========Stack==========\n");
    PrintStack(&(proc->stk), proc->stk.name, file, function, line);
    printf("=========================\n\n");

    printf("=======Call stack========\n");
    PrintStack(&(proc->call_stk), proc->stk.name, file, function, line);
    printf("=========================\n\n");

    printf("======Register Array=====\n");
    for (size_t i = 0; i < REGISTER_COUNT; i++)
    {
        printf("\tIn %s = %d\n", REG_DICTIONARY[i].name, proc->reg_array[i]);
    }
    printf("=========================\n\n");

    printf("======Commands Array=====\n");
    for (size_t i = 0; i < proc->buf_size; i++)
    {
        printf("| %.4d |", i);
    }
    printf("\n");
    for (size_t i = 0; i < proc->buf_size; i++)
    {
        printf("| %.4d |", proc->cmd_array[i]);
    }
    printf("\n=========================\n\n");

    printf("============RAM==========\n");
    for (size_t i = 0; i * i < MAX_SIZE_OF_RAM; i++)
    {
        for (size_t j = 0; j * j < MAX_SIZE_OF_RAM; j++)
        {
            printf("| 5%.4d |", proc->ram[i * MAX_LEN_OF_STR + j]);
        }
        printf("\n");
    }
    printf("=========================\n\n");

    printf("=======Video memory======\n");
    for (size_t i = 0; i * i < MAX_SIZE_OF_VM; i++)
    {
        for (size_t j = 0; j * j < MAX_SIZE_OF_VM; j++)
        {
            if (proc->ram[i * MAX_SIZE_OF_VM_STR + j + BEGIN_OF_VM] == 0)
            {
                printf(".");
            }
            else
            {
                printf("*");
            }
        }
        printf("\n");
    }
    printf("=========================\n\n");
}
