<h1 align="center">PREPROCESSOR</h1>
<h2 align="left">Description</h2>
My realization of working soft processing unit. What this project can do?<br>
    &emsp; 1) This project can translate assembler code to machine code. Code, which does it, locates in folder "Assembler"<br>
    &emsp; 2) Execute machine code. Code, which does it, locates in folder "SPU" <br>
    &emsp; 3) Translate from machine code to assembler code. Code, which does it, locates in folder "DisAssembler"<br>
<br>
About basic functions in "assembler": <br>
&emsp; 1) <code> PUSH < RAM | REG | NUM > </code> -- add argument with type specified in parentheses <br>
&emsp; 2) <code> IN </code>  -- read from input the number  and add it to stack <br> 
&emsp; 3) <code> POP < RAM | REG > </code> -- retrieves an element from the stack adds it to register or RAM <br>
&emsp; 4) <code> ADD </code> -- pops 2 numbers from stack and add their sum to stack <br>
&emsp; 6) <code> SUB </code> -- pops 2 numbers from stack and add their difference to stack <br>
&emsp; 7) <code> MUL </code> -- pops 2 numbers from stack and add their product to stack <br>
&emsp; 8) <code> DIV </code> -- pops 2 numbers from stack and add their quotient to stack <br>
&emsp; 9) <code> SQRT </code> -- pop number from stack and add square root of it <br>
&emsp; 10) <code> SIN </code> -- pop number from stack and add sin(number) <br>
&emsp; 11) <code> COS </code> -- pop number from stack and add cos(number) <br>
&emsp; 12) <code> OUT </code> -- pop number from stack and print it <br>
&emsp; 13) <code> HLT </code> -- exit from program <br>
&emsp; 14) <code> JMP < LBL > </code> -- go to line <br>
&emsp; 15) <code> JA < LBL > </code>  -- pop 2 numbers from stack, if first "<" second, then go to line <br>
&emsp; 16) <code> JAE < LBL > </code> -- pop 2 numbers from stack, if first "<=" second, then go to line <br>
&emsp; 17) <code> JB < LBL > </code>  -- pop 2 numbers from stack, if first "> second, then go to line <br>
&emsp; 18) <code> JBE < LBL > </code> -- pop 2 numbers from stack, if first ">=" second, then go to line <br>
&emsp; 19) <code> JE < LBL > </code>  -- pop 2 numbers from stack, if first "==" second, then go to line <br>
&emsp; 20) <code> JNE < LBL > </code> -- pop 2 numbers from stack, if first "!=" second, then go to line <br>
&emsp; 22) <code> CALL < LBL > </code> -- go to label, and add the last line to call stack <br>
&emsp; 23) <code> RET </code> -- pop label from stack and go to it <br>
&emsp; 24) <code> PUTC </code> -- pop number from stack and print it such as symbol <br>
&emsp; 25) <code> SET_PIXEL </code> -- dyes pixel(rbx, rax) color = RAM[rcx]  <br>
&emsp; 26) <code> CREATE_WINDOW </code> -- create window 256 by 256 <br>
<br>
The project supports DSL. You can add new commands!!! What you need to do: <br>
    &emsp; 1) Open in folder "DSL" file "commands.dsl" <br>
    &emsp; 2) Write in the end of file: <code>DEF_CMD((a), (b), (c), (d), (e))</code> <br>
        &emsp; &emsp; 2.1) In brackets you need write: <br>
                &emsp; &emsp; &emsp; <code>(a)</code> name of command <br>
                &emsp; &emsp; &emsp; <code>(b)</code> number of command <br>
                &emsp; &emsp; &emsp; <code>(c)</code> type of arguments <br>
                &emsp; &emsp; &emsp; <code>(d)</code> number of arguments (now better to write 0 or 1, if you write more, can be errors in program) <br>
                &emsp; &emsp; &emsp; <code>(e)</code> action, what program needs to do <br>
        &emsp; &emsp; 2.2) About syntax DSL you can read: [link to manual will be here later] <br>
<br>
<h2 align="left" How to launch and use program?></h2>
    &emsp; 1) write in terminal: <code>git clone https://github.com/Ch1n-ch1nless/Preprocessor.git</code> <br>
    &emsp; 2) go to folder "Preprocessor" <br>
    &emsp; 3) add folder "object" in folders: "Assembler", "SPU", "DisAssembler", "Stack", "Onegin" <br>
    &emsp; 4) write in terminal: <code>make compile</code> <br>
    <br>
    &emsp; After write commands, which writes in section 'Programs' <br>
<br>
<h2 align="left">Programs</h2>
Examples of programs that are written in "assembly" you can find in folder "Programs" <br>
What programs you can find? <br>
<h4 align="center">Factorial</h4>
&emsp; <code>Brief:</code> &emsp; This program on input takes number and returns it factorial <br> 
<br>
&emsp; <code>Command:</code> write in terminal: <code>make factorial</code> <br>
<br>
&emsp; <code>Example of working:</code> &emsp; <br>
<p align="center"><img src="/Img/factorial.png" width = "70%"></p>
<br>
<h4 align="center">Fibonacci</h4>
&emsp; <code>Brief:</code> &emsp; This program on input takes the index of fibonacci number and returns the fibonacci number with this index <br> 
<br>
&emsp; <code>Command:</code> write in terminal: <code>make fibonacci</code> <br>
<br>
&emsp; <code>Example of working:</code> &emsp; <br>
<p align="center"><img src="/Img/fibonacci.png" width = "70%"></p>
<br>
<h4 align="center">Moon</h4>
&emsp; <code>Brief:</code> &emsp; This program draws beatiful moon <br> 
<br>
&emsp; <code>Command:</code> write in terminal: <code>make moon</code> <br>
<br>
&emsp; <code>Example of working:</code> &emsp; <br>
<p align="center"><img src="/Img/moon.png" width = "70%"></p>
<br>
<h4 align="center">Square equation</h4>
&emsp; <code>Brief:</code> &emsp; This program on input takes 3 coefficients of the square equation and returns the number of roots and their valueы<br> 
&emsp; About return: <br>
&emsp; &emsp; 1) if first number is 0, that means equation hasn't roots. <br>
&emsp; &emsp; 2) if first number is 8, that means equation has infinite quantite of roots. <br>
&emsp; &emsp; 3) if first number is 1, that means equation hasn 1 root. Second number is value of root<br>
&emsp; &emsp; 4) if first number is 2, that means equation hasn 2 roots. Next 2 numbers are values of roots<br>
<br>
&emsp; <code>Command:</code> write in terminal: <code>make square_equation</code> <br>
<br>
&emsp; <code>Example of working:</code> &emsp; <br>
<p align="center"><img src="/Img/square_equation.png" width = "70%"></p>
