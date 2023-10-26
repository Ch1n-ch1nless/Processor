#include "spu_struct.h"

error_t ProcessorCtor(Processor* clm)
{
    assert(clm);

    error_t error = NO_ERR;

    error = STACK_CTOR(&(clm->stk));

    clm->reg_array = (elem_t*) calloc(REGISTER_COUNT, sizeof(elem_t));
    if (clm->reg_array == nullptr)
    {
        error = MEM_ALLOC_ERR;
    }

    clm->ram = (elem_t*) calloc(MAX_SIZE_OF_RAM, sizeof(elem_t));
    if (clm->ram == nullptr)
    {
        error = MEM_ALLOC_ERR;
    }

    return error;
}

error_t ProcessorDtor(Processor* clm)
{
    assert(clm);

    error_t error = NO_ERR;

    error = StackDtor(&(clm->stk));

    free(clm->reg_array);
    clm->reg_array = nullptr;

    free(clm->cmd_array);
    clm->cmd_array = nullptr;

    free(clm->ram);
    clm->ram = nullptr;

    clm->buf_size = 0;

    return error;
}

error_t ProcessorStkPush(Processor* clm, elem_t new_value)
{
    assert(clm);

    error_t error = NO_ERR;

    error = StackPush(&(clm->stk), new_value);

    return error;
}

error_t ProcessorStkPop(Processor* clm, elem_t* ret_value)
{
    assert(clm);

    error_t error = NO_ERR;

    error = StackPop(&(clm->stk), ret_value);

    return error;
}

error_t ProcessorRegPush(Processor* clm, size_t index)
{
    assert(clm);

    error_t error = NO_ERR;

    elem_t new_value = POISON_VALUE;

    error = StackPop(&(clm->stk), &new_value);

    clm->reg_array[index] = new_value;

    return error;
}

error_t ProcessorRegPop(Processor* clm, size_t index)
{
    assert(clm);

    error_t error = NO_ERR;

    elem_t ret_value = clm->reg_array[index];

    error = StackPush(&(clm->stk), ret_value);

    return error;
}

error_t ProcessorVerify(Processor* clm)
{
    error_t error = StackVerify(&(clm->stk));

    if (clm->reg_array == nullptr)
    {
        error |= REG_ARRAY_NULLPTR_ERR;
    }

    if (clm->cmd_array == nullptr)
    {
        error |= CMD_ARRAY_NULLPTR_ERR;
    }

    return error;
}

void ProcessorError(Processor* clm, error_t error, const char* file, const char* function, const int line)
{
    PRINT_ERROR(&(clm->stk), error);

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

void ProcessorDump(Processor* clm, const char* spu_name, const char* file,
                               const char* function, const int   line)
{
    printf("Processor \"%s\": [%p]\n", spu_name, clm);
    printf("called from file: %s(%d) in function: %s\n{\n", file, line, function);
    PrintStack(&(clm->stk), clm->stk.name, file, function, line);

    printf("======Register Array=====\n");
    for (size_t i = 0; i < REGISTER_COUNT; i++)
    {
        printf("\tIn %s = %d\n", REGISTERS_DICTIONARY[i].name, clm->reg_array[i]);
    }
    printf("=========================\n\n");

    printf("======Commands Array=====\n");
    for (size_t i = 0; i < clm->buf_size; i++)
    {
        printf("| %.4d |", i);
    }
    printf("\n");
    for (size_t i = 0; i < clm->buf_size; i++)
    {
        printf("| %.4d |", clm->cmd_array[i]);
    }
    printf("\n=========================\n\n");

    printf("============RAM==========\n");
    for (size_t i = 0; i * i < MAX_SIZE_OF_RAM; i++)
    {
        for (size_t j = 0; j * j < MAX_SIZE_OF_RAM; j++)
        {
            printf("| %.4d |", clm->ram[i * MAX_SIZE_OF_RAM + j]);
        }
        printf("\n");
    }
    printf("=========================\n\n");
}
