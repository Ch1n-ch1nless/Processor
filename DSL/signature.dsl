DEF_SGNT(NONE,  0, {return;})
DEF_SGNT(NUM,   5, {
                    MAKE_VAR(number)
                    if (sscanf(str_arg, "%d", &number) == 1)
                    {
                        cmd_array[i] += NUM;
                        i++;
                        cmd_array[i] = number;
                    }
                   })
DEF_SGNT(REG,   6, {
                    for (size_t k = 0; k < REGISTER_COUNT; k++)
                    {
                        if (strnicmp(str_arg, REGISTERS_DICTIONARY[k].name, REGISTERS_DICTIONARY[k].len) == 0)
                        {
			    cmd_array[i] += REG;
                            i += 1;
                            cmd_array[i] = REGISTERS_DICTIONARY[k].num;
                        }
                    }
                   })

DEF_SGNT(LBL,   7, {
                    for (size_t k = 0; k < LABELS_COUNT; k++)
                    {
                        if (strnicmp(str_arg, LABELS_ARRAY[k].name, LABELS_ARRAY[k].len) == 0)
                        {
                            cmd_array[i] += LBL;
                            i += 1;
                            cmd_array[i] = LABELS_ARRAY[k].line;
                        }
                    }
                   })