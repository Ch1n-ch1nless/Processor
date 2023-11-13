#define GET_SGNT(signature) int signature = proc->cmd_array[cmd_index] & BITMASK_SGNT;

#define MAKE_VAR(name) elem_t name = 35;

#define MAKE_PTR(pointer, name) elem_t* pointer = &name;

#define GET_ARG(signature, argument, arg_pointer)                          \
        cmd_index++;                                                       \
        GetArgument(proc, cmd_index,  signature, &argument, &arg_pointer);

#define GET_LBL(cmd_index) cmd_index = proc->cmd_array[cmd_index+1] - 1;

#define STK_PUSH(number) ProcessorStkPush(proc, number);

#define STK_POP(pointer)  ProcessorStkPop(proc, pointer);

#define CALL_STK_PUSH(number)   StackPush(&(proc->call_stk), number);

#define CALL_STK_POP(number)    StackPop(&(proc->call_stk), &number);

#define READ(number) scanf(elem_format, &number);

#define SQRT(number) number = (elem_t) sqrt((double) number);

#define SIN(number) number = (elem_t) sin((double) number);

#define COS(number) number = (elem_t) cos((double) number);

#define WRITE(x) printf(elem_format, x);

#define SIGNAL_ERROR printf("ERROR! The wrong syntax!\n");

#define MAKE_COLOR(color, rgb)  int red   = color / 65536;              \
                                int green = color / 256 % 256;          \
                                int blue  = color % 256;                \
                                COLORREF rgb = RGB(red, green, blue);

#define SKIP_LINE printf("\n");

#define BREAK break;

#define EXIT  return error;

#define DEF_JMP_CMD(name, num, num_of_args, compare)                                                \
        DEF_CMD(name, num, LBL, num_of_args, {                                                      \
                                            if (num_of_args == 1)                                   \
                                            {                                                       \
                                                cmd_index = proc->cmd_array[cmd_index + 1] - 1;     \
                                            }                                                       \
                                            else if (num_of_args == 2)                              \
                                            {                                                       \
                                                elem_t first  = POISON_VALUE;                       \
                                                elem_t second = POISON_VALUE;                       \
                                                ProcessorStkPop(proc, &second);                     \
                                                ProcessorStkPop(proc, &first);                      \
                                                if (first compare second)                           \
                                                {                                                   \
                                                    cmd_index = proc->cmd_array[cmd_index + 1] - 1; \
                                                }                                                   \
                                                else                                                \
                                                {                                                   \
                                                    cmd_index++;                                    \
                                                }                                                   \
                                            }                                                       \
                                            else                                                    \
                                            {                                                       \
                                                error |= INCORRECT_NUM_OF_ARGS_ERR;                 \
                                                CHECK_PROC_ERR(error, proc)                         \
                                            }                                                       \
                                             })
