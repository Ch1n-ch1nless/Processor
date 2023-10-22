#define GET_SGNT(data_type) data_type = spu->cmd_array[i] & BIT_MASK_OF_ARGS;

#define GET_ARG(number) i++; number = spu->cmd_array[i];

#define STK_PUSH(number) ProcessorStkPush(spu, number);

#define STK_POP(number)  ProcessorStkPop(spu, &number);

#define REG_PUSH(number) ProcessorRegPush(spu, number);

#define REG_POP(number)  ProcessorRegPop(spu, number);

#define PRINT(text) printf(#text);

#define READ(number) scanf(elem_format, &number);

#define MAKE_VAR(name) int name = 0;

#define WRITE(x) printf(elem_format "\n", x);

#define SIGNAL_ERROR printf("ERROR! The wrong syntax!");

#define BREAK break;

#define EXIT return;
