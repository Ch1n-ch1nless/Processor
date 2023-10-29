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
        write <code>.\asm.exe Assembler_commands/circle.asm Assembler_commands/commands.bin</code> in terminal
        write <code>.\spu.exe Assembler_commands/commands.bin</code> in terminal
        write <code>.\dism.exe Assembler_commands/commands.bin</code> in terminal

## Feats

* This project can assemble, disassemble and process code

* Jumps are supported

* Registers are supported

* Labels are supported

* Functions are supported

* Ram is supported

* Implemented functions:
    * <code> PUSH < register | num | ram > </code>
    * <code> IN </code>
    * <code> POP < register | ram > </code>
    * <code> ADD </code>
    * <code> SUB </code>
    * <code> MUL </code>
    * <code> DIV </code>
    * <code> SQRT </code>
    * <code> SIN </code>
    * <code> COS </code>
    * <code> OUT </code>
    * <code> HLT </code>
    * <code> JMP < lable | num > </code>
    * <code> JA < lable | num > </code>
    * <code> JAE < lable | num > </code>
    * <code> JB < lable | num > </code>
    * <code> JBE < lable | num > </code>
    * <code> JE < lable | num > </code>
    * <code> JNE < lable | num > </code>
    * <code> JMON < lable | num > </code>
    * <code> CALL < lable > </code>
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
**This project is created by [bai_tim](https://github.com/bai_tim)**
