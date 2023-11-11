#ifndef REGISTERS_H_INCLUDED
#define REGISTERS_H_INCLUDED

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

const Register REG_DICTIONARY[REGISTER_COUNT] =  {
                                                    #include "../DSL/registers.dsl"
                                                  };

#undef DEF_REG

#endif // REGISTERS_H_INCLUDED
