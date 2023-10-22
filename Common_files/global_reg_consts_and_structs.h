#ifndef GLOBAL_REG_CONSTS_AND_STRUCTS_H_INCLUDED
#define GLOBAL_REG_CONSTS_AND_STRUCTS_H_INCLUDED

#define DEF_REG(name) name,

enum REGS : unsigned int
{
    #include "../DSL/registers.dsl"
    REGISTER_COUNT
};

#undef DEF_REG

struct Register
{
    const char*   name;
    const size_t  len;
    const int     num;
};

#define DEF_REG(name) {#name, strlen(#name), name},

static Register REGISTERS_DICTIONARY[REGISTER_COUNT] =  {
                                                            #include "../DSL/registers.dsl"
                                                        };

#undef DEF_REG

#endif // GLOBAL_REG_CONSTS_AND_STRUCTS_H_INCLUDED
