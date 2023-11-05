#ifndef LABELS_H_INCLUDED
#define LABELS_H_INCLUDED

#include "../../Onegin/source/text.h"

const size_t MAX_SIZE_OF_CAPACITY = 100;

struct Label
{
    char*  str   = nullptr;
    size_t len   = 0;
    int    line  = 0;
};

struct LabelTable
{
    size_t size     = 0;
    size_t capacity = 0;
    Label* array    = nullptr;
};

error_t  LabelTableCtor(LabelTable* lbl_table);
error_t  LabelTableDtor(LabelTable* lbl_table);

error_t  LabelTablePush(LabelTable* lbl_table, Label lbl);
error_t  LabelTablePop(LabelTable* lbl_table, size_t index, Label* ret_lbl);

error_t LabelTableVerify(LabelTable* lbl_table);

void    LabelTableError(LabelTable* lbl_table, error_t error);

void    LabelTableDump(LabelTable* lbl_table);

error_t  MakeNewLabel(char* lbl_str, Label* new_lbl, size_t index);

#endif // LABELS_H_INCLUDED
