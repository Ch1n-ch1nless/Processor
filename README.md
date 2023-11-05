<h1 align="center">PROCESSOR</h1>

<h2 align="left"> Description </h2>

 This is my project, which imitate working of processor.
 It has the graph library, which works ONLY ON WINDOWS!!!
 On other OS it won't launch!

<h2 align="left"> How to install and use? </h2>

1. Clone <br>
        write <code>git clone https://github.com/Ch1n-ch1nless/Preprocessor.git</code> in terminal

2. Go to folder <br>
        write <code>cd Preprocessor</code> in terminal

3. Build <br>
        <a>write <code>make

<h2 align="left">Note!</h2>
If you want launch another file, you have 2 ways to fix this problem:
<br>
        1. You can change name of file in makefile1 and repeat the previous step:
        <p align="center"><img src="/Img/makefile_change.png" width = "50%"></p>
<br>
        2. You build project, and after write 2 commands: (filename - name of file, which you want launch) <br>
        <code> .\asm.exe Assembler_commands/filename.asm Assembler_commands/commands.bin </code> <br>
        <code> .\spu.exe Assembler_commands/commands.bin  </code> <br>

<h2 align="left"> Warning! </h2>
The project has problem with Disassembler. <br>
If you want launch without Disassembler, you need to do next steps:
* write in terminal: <code>make run_asm </code>
* write in terminal: <code>make run_spu </code>



<h2 align="left">What can this project do?</h2>

This project can: <br>
    * assemble code
    <br>
    * disassemble machine code
    <br>
    * execute commands
    <br>

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
    * <code> SET_PIXEL </code>
    * <code> CREATE_WINDOW </code>



<h2 align="left">Examples</h2>

Fibonacci: <br>
<p align="center"><img src="/Img/fibonacci.png" width = "70%"></p>

Beautiful Moon: <br>
<p align="center"><img src="/Img/moon.png" width = "70%"></p>

Square equation: <br>
<p align="center"><img src="/Img/square_equation.png" width = "70%"></p>

<h2 align="left">Support</h2>
**This project is created by [Ch1n-ch1nless](https://github.com/Ch1n-ch1nless)**
