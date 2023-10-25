#ifndef LABELS_H_INCLUDED
#define LABELS_H_INCLUDED

const size_t MAX_SIZE_OF_CAPACITY = 100;

struct Label
{
    char* str    = nullptr;
    size_t len   = 0;
    int    line  = 0;
};

struct Fix_up
{
    size_t cmd_index = 0;
    size_t lbl_index = 0;
};

#endif // LABELS_H_INCLUDED
