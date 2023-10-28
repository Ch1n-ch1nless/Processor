#ifndef LABELS_H_INCLUDED
#define LABELS_H_INCLUDED

#include "../../Onegin/source/text.h"

typedef unsigned long long error_t;

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

ERRORS  LabelTableCtor(LabelTable* lbl_table);
ERRORS  LabelTableDtor(LabelTable* lbl_table);

ERRORS  LabelTablePush(LabelTable* lbl_table, Label lbl);
ERRORS  LabelTablePop(LabelTable* lbl_table, size_t index, Label* ret_lbl);

error_t LabelTableVerify(LabelTable* lbl_table);

void    LabelTableError(LabelTable* lbl_table, error_t error);

void    LabelTableDump(LabelTable* lbl_table);

ERRORS  MakeNewLabel(char* lbl_str, Label* new_lbl, size_t index);

#endif // LABELS_H_INCLUDED
