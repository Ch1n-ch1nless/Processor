<h1 align="center">PROCESSOR</h1>

## Description

 Implementation of processor.

## How to use

1. Clone <br>
        write <code>git clone https://github.com/Ch1n-ch1nless/Preprocessor.git in terminal

2. Go to folder <br>
        write <code>cd Preprocessor</code> in terminal

3. Build <br>
        write <code>make -f make_asm</code> in terminal
        write <code>make -f make_spu</code> in terminal
        write <code>make -f make_dis</code> in terminal

5. Run <br>
        write <code>.\asm.exe Assembler_commands/circle.asm Assembler_commands/commands.bin</code> in terminal (It will launch circle.asm, if you want launch another file, instead write it) 
        write <code>.\spu.exe Assembler_commands/commands.bin</code> in terminal
        write <code>.\dism.exe Assembler_commands/commands.bin</code> in terminal

## Feats

This project can:
    * assemble code
    * disassemble 
    * execute commands

Project supports DSL to create new features, 

* Basic functions:
    * <code> PUSH < RAM | REG | NUM > </code>
    * <code> IN </code>
    * <code> POP < RAM | REG > </code>
    * <code> ADD </code>
    * <code> SUB </code>
    * <code> MUL </code>
    * <code> DIV </code>
    * <code> SQRT </code>
    * <code> SIN </code>
    * <code> COS </code>
    * <code> OUT </code>
    * <code> HLT </code>
    * <code> JMP < LBL > </code>
    * <code> JA < LBL > </code>
    * <code> JAE < LBL > </code>
    * <code> JB < LBL > </code>
    * <code> JBE < LBL > </code>
    * <code> JE < LBL > </code>
    * <code> JNE < LBL > </code>
    * <code> JMON < LBL > </code>
    * <code> CALL < LBL > </code>
    * <code> RET </code>
    * <code> PUTC </code>



## Examples

Factorial: <br>
<p align="center"><img src="/images/Factorial.png" width = "70%"></p>

Circle: <br>
<p align="center"><img src="/images/Circle.png" width = "70%"></p>

Quadratic equation: <br>
<p align="center"><img src="/images/Quadratic_equation.png" width = "70%"></p>

## Support
**This project is created by [bai_tim](https://github.com/Ch1n-ch1nless)**
