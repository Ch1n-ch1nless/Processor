#ifndef CONFIG_SGNT_H_INCLUDED
#define CONFIG_SGNT_H_INCLUDED

#define DEF_SGNT(name, number, ...) name = 1 << number,

enum ArgTypes : unsigned int
{
    #include "../DSL/signature.dsl"
};

#undef DEF_SGNT

#endif // CONFIG_SGNT_H_INCLUDED
