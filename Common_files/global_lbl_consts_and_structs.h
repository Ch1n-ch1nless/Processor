#ifndef GLOBAL_LBL_CONSTS_AND_STRUCTS_H_INCLUDED
#define GLOBAL_LBL_CONSTS_AND_STRUCTS_H_INCLUDED

#define DEF_LABEL(name, value) {#name, strlen(#name), value, -1},

struct Label
{
    const char* name;
    size_t len;
    const size_t value;
    int line;
};

static Label LABELS_ARRAY[] = {
                                #include "../DSL/labels.dsl"
                              };

#undef DEF_LABEL

const size_t LABELS_COUNT = 2;

#endif // GLOBAL_LBL_CONSTS_AND_STRUCTS_H_INCLUDED
