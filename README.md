<h1 align="center">PROCESSOR</h1>

## Description

 Implementation of processor.

## How to use

1. Clone <br>
        write <code>git clone https://github.com/Ch1n-ch1nless/Preprocessor.git</code> in terminal
   
2. Go to folder <br>
        write <code>cd Preprocessor</code> in terminal
   
3. Build <br>
        <a>write <code>make -f makefile1</code> in terminal</a>
        </br>
        <br>
        <a>write <code>make -f makefile2</code> in terminal</a>

<h2 align="left">Note!</h2>
If you want launch another file, you have 2 ways to fix this problem:
<br>
        1. You can change name of file in makefile1 and repeat the previous step:
        <p align="center"><img src="/Img/makefile_change.png" width = "50%"></p>
</br>
<br>
        2. You build project, and after write 2 commands: (filename - name of file, which you want launch)
        <code> .\asm.exe Assembler_commands/filename.asm Assembler_commands/commands.bin </code>
        <code> .\spu.exe Assembler_commands/commands.bin  </code>
        
    

## What can this project do?

This project can: <br>
    * assemble code
    </br>
    <br>
    * disassemble
    </br>
    <br>
    * execute commands
    </br>

You can use: RAM, registers, video memory

Project supports DSL to create new features:

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

Fibonacci: <br>
<p align="center"><img src="/Img/fibonacci.png" width = "70%"></p>

Circle: <br>
<p align="center"><img src="/Img/circle.png" width = "70%"></p>

Square equation: <br>
<p align="center"><img src="/Img/square_equation.png" width = "70%"></p>

## Support
**This project is created by [Ch1n-ch1nless](https://github.com/Ch1n-ch1nless)**
