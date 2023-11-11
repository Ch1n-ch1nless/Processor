#ifndef SIGNATURES_H_INCLUDED
#define SIGNATURES_H_INCLUDED

enum ArgTypes : unsigned int
{
    NONE = 0,
    NUM  = 1 << 5,
    REG  = 1 << 6,
    LBL  = 1 << 7,
    RAM  = 1 << 8
};

#endif // SIGNATURES_H_INCLUDED
