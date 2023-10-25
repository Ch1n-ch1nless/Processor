#define GET_SGNT(data_type) data_type = clm->cmd_array[i] & BITMASK_SGNT;

#define GET_ARG(number) i++; number = clm->cmd_array[i];

#define STK_PUSH(number) ProcessorStkPush(clm, number);

#define STK_POP(number)  ProcessorStkPop(clm, &number);

#define REG_PUSH(number) ProcessorRegPush(clm, number);

#define REG_POP(number)  ProcessorRegPop(clm, number);

#define PRINT(text) printf(#text);

#define READ(number) scanf(elem_format, &number);

#define MAKE_VAR(name) elem_t name = 0;

#define WRITE(x) printf(elem_format "\n", x);

#define SIGNAL_ERROR printf("ERROR! The wrong syntax!\n");

#define BREAK break;

#define EXIT  break;
