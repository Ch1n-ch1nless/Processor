#include "label.h"

error_t LabelTableCtor(LabelTable* lbl_table)
{
    assert(lbl_table);

    error_t error = NO_ERR;

    lbl_table->size = 0;

    lbl_table->capacity = MAX_SIZE_OF_CAPACITY;

    lbl_table->array = (Label*) calloc(lbl_table->capacity, sizeof(Label));
    if (lbl_table->array == nullptr)
    {
        return error | MEM_ALLOC_ERR;
    }

    return error;
}

error_t LabelTableDtor(LabelTable* lbl_table)
{
    assert(lbl_table);
    assert(lbl_table->array);

    error_t error = NO_ERR;

    lbl_table->size = 0;

    lbl_table->capacity = 0;

    free(lbl_table->array);
    lbl_table->array = nullptr;

    return error;
}

error_t LabelTablePush(LabelTable* lbl_table, Label lbl)
{
    assert(lbl_table);
    assert(lbl_table->array);

    error_t error = NO_ERR;

    if (lbl_table->size >= lbl_table->capacity)
    {
        Label* temp_ptr = lbl_table->array;

        lbl_table->capacity *= 2;

        temp_ptr = (Label*) realloc(lbl_table->array, lbl_table->capacity);
        if (temp_ptr == nullptr)
        {
            return error | MEM_ALLOC_ERR;
        }
    }

    lbl_table->array[lbl_table->size] = lbl;

    lbl_table->size++;

    return error;
}

error_t LabelTablePop(LabelTable* lbl_table, size_t index, Label* ret_lbl)
{
    assert(lbl_table);
    assert(lbl_table->array);
    assert(ret_lbl);

    error_t error = NO_ERR;

    if (index < lbl_table->size)
    {
        *ret_lbl = lbl_table->array[index];
    }
    else
    {
        return error | BAD_MEM_ACS_ERR;
    }

    return error;
}

error_t LabelTableVerify(LabelTable* lbl_table)
{
    assert(lbl_table);

    error_t error = NO_ERR;

    if (lbl_table->size > lbl_table->capacity)
    {
        error |= CAPACITY_FEWER_SIZE_ERR;
    }

    if (lbl_table->array == nullptr)
    {
        error |= NULL_ARR_ERR;
    }

    return error;
}

void LabelTableError(LabelTable* lbl_table, error_t error)
{
    if (error & CAPACITY_FEWER_SIZE_ERR)
    {
        fprintf(stderr, "ERROR!!! Size of array [%d] > capacity of array [%d]!!!\n",
                lbl_table->size, lbl_table->capacity);
    }

    if (error & NULL_ARR_ERR)
    {
        fprintf(stderr, "ERROR!!! The pointer to array is NULL!!!\n");
    }

    if (error & MEM_ALLOC_ERR)
    {
        fprintf(stderr, "ERROR!!! Program can NOT allocate memory!!!\n");
    }

    if (error & BAD_MEM_ACS_ERR)
    {
        fprintf(stderr, "ERROR!!! Attempt to read beyond the array!!!\n");
    }
}

void LabelTableDump(LabelTable* lbl_table)
{
    assert(lbl_table);

    printf("=====Label table=====\n");
    printf("\tSize     = %d\n", lbl_table->size);
    printf("\tCapacity = %d\n", lbl_table->capacity);
    printf("\n");
    printf("\tArray:\n");
    for (size_t i = 0; i < lbl_table->size; i++)
    {
        printf("\t\t[%d] := %s[%d]\n", i, lbl_table->array[i].str, lbl_table->array[i].line);
    }
    printf("\n=====================\n");
}

error_t MakeNewLabel(char* lbl_str, Label* new_lbl, size_t index)
{
    error_t error = NO_ERR;

    new_lbl->str = lbl_str;

    new_lbl->line = index;

    size_t size_lbl = 0;

    while (isalpha(lbl_str[size_lbl]) || lbl_str[size_lbl] == '_')
    {
        size_lbl++;
    }

    new_lbl->len = size_lbl;

    return error;
}
