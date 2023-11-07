#define GET_SGNT(data_type) data_type = proc->cmd_array[cmd_index] & BITMASK_SGNT;

#define GET_ARG(number) cmd_index++; number = proc->cmd_array[cmd_index];

#define STK_PUSH(number) ProcessorStkPush(proc, number);

#define STK_POP(number)  ProcessorStkPop(proc, &number);

#define REG_PUSH(number) ProcessorRegPush(proc, number);

#define REG_POP(number)  ProcessorRegPop(proc, number);

#define RAM_POP(index)   elem_t x = 0;              \
                         ProcessorStkPop(proc, &x); \
                         proc->ram[index] = x;

#define RAM_PUSH(index)  elem_t x = proc->ram[index]; \
                         ProcessorStkPush(proc, x);

#define PUSH_CALL(number)   StackPush(&(proc->call_stk), number);

#define POP_CALL(number)    StackPop(&(proc->call_stk), &number);

#define READ(number) scanf(elem_format, &number);

#define MAKE_VAR(name) elem_t name = 0;

#define WRITE(x) printf(elem_format, x);

#define SIGNAL_ERROR printf("ERROR! The wrong syntax!\n");

#define MAKE_COLOR(color, rgb)  int red   = color / 65536;              \
                                int green = color / 256 % 256;          \
                                int blue  = color % 256;                \
                                COLORREF rgb = RGB(red, green, blue);

#define SKIP_LINE printf("\n");

#define BREAK break;

#define EXIT  return error;
