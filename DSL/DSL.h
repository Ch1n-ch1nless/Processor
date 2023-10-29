#define GET_SGNT(data_type) data_type = clm->cmd_array[cmd_index] & BITMASK_SGNT;

#define GET_ARG(number) cmd_index++; number = clm->cmd_array[cmd_index];

#define STK_PUSH(number) ProcessorStkPush(clm, number);

#define STK_POP(number)  ProcessorStkPop(clm, &number);

#define REG_PUSH(number) ProcessorRegPush(clm, number);

#define REG_POP(number)  ProcessorRegPop(clm, number);

#define RAM_PUSH(index)  elem_t x = 0;             \
                         ProcessorStkPop(clm, &x); \
                         clm->ram[index] = x;

#define RAM_POP(index)   elem_t x = clm->ram[index]; \
                         ProcessorStkPush(clm, x);

#define READ(number) scanf(elem_format, &number);

#define MAKE_VAR(name) elem_t name = 0;

#define WRITE(x) printf(elem_format, x);

#define SIGNAL_ERROR printf("ERROR! The wrong syntax!\n");

#define BREAK break;

#define EXIT  break;
