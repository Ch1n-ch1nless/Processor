#include "DSL.h"

DEF_CMD(PUSH,  1, REG | NUM, 1, {
                                    MAKE_VAR(data_type)
                                    GET_SGNT(data_type)
				    MAKE_VAR(number)
				    GET_ARG(number)
                                    switch(data_type)
                                    {
                                        case(REG):
                                            REG_PUSH(number)
                                            BREAK

                                        case(NUM):
                                            STK_PUSH(number)
                                            BREAK

                                        default:
                                            SIGNAL_ERROR
                                            BREAK
                                    }
                                })

DEF_CMD(IN,    2, NONE,      0, {
                                    PRINT(Print the number: )
                                    MAKE_VAR(number)
                                    READ(number)
                                    STK_PUSH(number)
                                })
DEF_CMD(HLT,  -1, NONE,      0, {EXIT}   )
DEF_CMD(ADD,   3, NONE,      0, {
                                    MAKE_VAR(x)
                                    MAKE_VAR(y)
                                    STK_POP(y)
                                    STK_POP(x)
                                    STK_PUSH(x + y)
                                })
DEF_CMD(SUB,   4, NONE,      0, {
                                    MAKE_VAR(x)
                                    MAKE_VAR(y)
                                    STK_POP(y)
                                    STK_POP(x)
                                    STK_PUSH(x - y)
                                })
DEF_CMD(MUL,   5, NONE,      0, {
                                    MAKE_VAR(x)
                                    MAKE_VAR(y)
                                    STK_POP(y)
                                    STK_POP(x)
                                    STK_PUSH(x * y)
                                })
DEF_CMD(DIV,   6, NONE,      0, {
                                    MAKE_VAR(x)
                                    MAKE_VAR(y)
                                    STK_POP(y)
                                    STK_POP(x)
                                    STK_PUSH(x / y)
                                })
DEF_CMD(SQRT,  7, NONE,      0, {
                                    MAKE_VAR(x)
                                    STK_POP(x)
                                    STK_PUSH(sqrt(x))
                                })
DEF_CMD(SIN,   8, NONE,      0, {
                                    MAKE_VAR(x)
                                    STK_POP(x)
                                    STK_PUSH(sin(x))
                                })
DEF_CMD(COS,   9, NONE,      0, {
                                    MAKE_VAR(x)
                                    STK_POP(x)
                                    STK_PUSH(cos(x))
                                })
DEF_CMD(OUT,  10, NONE,      0, {
                                    MAKE_VAR(x)
                                    STK_POP(x)
                                    WRITE(x)
                                })

DEF_CMD(POP,  11, REG,       1, {
                                    MAKE_VAR(data_type)
       	                            GET_SGNT(data_type)
                                    MAKE_VAR(number)
				    GET_ARG(number)
                                    switch(data_type)
                                    {
                                        case(REG):
                                            REG_POP(number)
                                            BREAK

                                        default:
                                            SIGNAL_ERROR
                                            BREAK
                                    }
                                })

DEF_CMD(JMP,  12, LBL,       1, {
				    i = clm->cmd_array[i+1] - 1;
                                })

DEF_CMD(JA,   13, LBL,       1, {
				    	MAKE_VAR(first)
					MAKE_VAR(second)
					STK_POP(second)
					STK_POP(first)
					if (first < second)
					{
					    i = clm->cmd_array[i+1] - 1;
					}
					else
					{
					    i += 1;
					}
                                })

DEF_CMD(JAE,  14, LBL,       1, {
				    MAKE_VAR(first)
					MAKE_VAR(second)
					STK_POP(second)
					STK_POP(first)
					if (first <= second)
					{
					    i = clm->cmd_array[i+1] - 1;
					}
					else
					{
					    i += 1;
					}
                                })

DEF_CMD(JB,   15, LBL,       1, {
				    MAKE_VAR(first)
					MAKE_VAR(second)
					STK_POP(second)
					STK_POP(first)
					if (first > second)
					{
					    i = clm->cmd_array[i+1] - 1;
					}
					else
					{
					    i += 1;
					}
                                })

DEF_CMD(JBE,  16, LBL,       1, {
				    MAKE_VAR(first)
					MAKE_VAR(second)
					STK_POP(second)
					STK_POP(first)
					if (first >= second)
					{
					    i = clm->cmd_array[i+1] - 1;
					}
					else
					{
					    i += 1;
					}
                                })

DEF_CMD(JE,   17, LBL,       1, {
				    MAKE_VAR(first)
					MAKE_VAR(second)
					STK_POP(second)
					STK_POP(first)
					if (first == second)
					{
					    i = clm->cmd_array[i+1] - 1;
					}
					else
					{
					    i += 1;
					}
                                })

DEF_CMD(JNE,  18, LBL,       1, {
				    MAKE_VAR(first)
					MAKE_VAR(second)
					STK_POP(second)
					STK_POP(first)
					if (first != second)
					{
					    i = clm->cmd_array[i+1] - 1;
					}
					else
					{
					    i += 1;
					}
                                })

DEF_CMD(CALL, 19, LBL,       1, {
				    StackPush(call_stk, i+1);
				    i = clm->cmd_array[i+1] - 1; 
                                })

DEF_CMD(RET, 20, NONE,       0, {
				    MAKE_VAR(index)
				    StackPop(call_stk, &index);
				    i = index; 
                                })

 