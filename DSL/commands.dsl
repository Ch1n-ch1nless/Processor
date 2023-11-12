#include "DSL.h"

DEF_CMD(PUSH,  1, REG | NUM | RAM, 1, {
					GET_SGNT(signature)
                                    	MAKE_VAR(argument)
					MAKE_PTR(arg_pointer, argument)
					GET_ARG(signature, argument, arg_pointer)
					STK_PUSH(argument)
				      })				

DEF_CMD(IN,    2, NONE,      0,	      {
                                    	MAKE_VAR(number)
                                    	READ(number)
                                    	STK_PUSH(number)
                                      })

DEF_CMD(HLT,   0, NONE,      0,       {EXIT})

DEF_CMD(ADD,   3, NONE,      0,       {
                                    	MAKE_VAR(x)
                                    	MAKE_VAR(y)
                                    	STK_POP(&y)
                                    	STK_POP(&x)
                                    	STK_PUSH(x + y)
                                      })
DEF_CMD(SUB,   4, NONE,      0,       {
                                    	MAKE_VAR(x)
                                    	MAKE_VAR(y)
                                    	STK_POP(&y)
                                    	STK_POP(&x)
                                    	STK_PUSH(x - y)
                                      })
DEF_CMD(MUL,   5, NONE,      0,       {
                                    	MAKE_VAR(x)
                                    	MAKE_VAR(y)
                                    	STK_POP(&y)
                                    	STK_POP(&x)
                                    	STK_PUSH(x * y)
                                      })
DEF_CMD(DIV,   6, NONE,      0,       {
                                    	MAKE_VAR(x)
                                    	MAKE_VAR(y)
                                    	STK_POP(&y)
                                    	STK_POP(&x)
                                    	STK_PUSH(x / y)
                                      })
DEF_CMD(SQRT,  7, NONE,      0,       {
                                    	MAKE_VAR(x)
                                    	STK_POP(&x)
					SQRT(x)
                                    	STK_PUSH(x)
                                      })
DEF_CMD(SIN,   8, NONE,      0,       {
                                    	MAKE_VAR(x)
                                    	STK_POP(&x)
					SIN(x)
                                    	STK_PUSH(x)
                                      })
DEF_CMD(COS,   9, NONE,      0,       {
                                   	MAKE_VAR(x)
                                    	STK_POP(&x)
					COS(x)
                                    	STK_PUSH(x)
                                      })
DEF_CMD(OUT,  10, NONE,      0,       {
                                    	MAKE_VAR(x)
                                    	STK_POP(&x)
                                    	WRITE(x)
					SKIP_LINE
                                      })

DEF_CMD(POP,  11, REG | RAM | NUM, 1, {
                                    	GET_SGNT(signature)
                                    	MAKE_VAR(argument)
					MAKE_PTR(arg_pointer, argument)
					GET_ARG(signature, argument, arg_pointer)
					STK_POP(arg_pointer)
                                      })

DEF_JMP_CMD(JMP, 12, 1, ==)

DEF_JMP_CMD(JA,  13, 2, < )

DEF_JMP_CMD(JAE, 14, 2, <=)

DEF_JMP_CMD(JB,  15, 2, > )

DEF_JMP_CMD(JBE, 16, 2, >=)

DEF_JMP_CMD(JE,  17, 2, ==)

DEF_JMP_CMD(JNE, 18, 2, !=)

DEF_CMD(CALL, 19, LBL,       1, {
				    CALL_STK_PUSH(cmd_index+1)
				    GET_LBL(cmd_index) 
                                })

DEF_CMD(RET, 20, NONE,       0, {
				    MAKE_VAR(index)
				    CALL_STK_POP(index);
				    cmd_index = index; 
                                })

DEF_CMD(PUTC, 21, NONE,     0, {
				    MAKE_VAR(symbol)
				    STK_POP(&symbol)
				    printf("%c", symbol);
      				})

DEF_CMD(SET_PIXEL, 22, NONE, 0, {
				    MAKE_VAR(color);
				    color = proc->ram[proc->reg_array[2]];
				    MAKE_COLOR(color, rgb);
				    txSetPixel(proc->reg_array[1], proc->reg_array[0], rgb);
				})

DEF_CMD(CREATE_WINDOW, 23, NONE, 0, {txCreateWindow(256, 256);})