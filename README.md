<h1 align="center">Hi there, I'm <a href="https://t.me/Chin_chinless" target="_blank">Oleg</a>
<img src="https://github.com/blackcater/blackcater/raw/main/images/Hi.gif" height="32"/></h1>
<h4 align="center">I am the author of project:</h4>
<h1 align="center">Preprocessor</h1>
<h2 align="left">Description</h2>
My realization of working soft processing unit. What this project can do?<br>
    &emsp; 1) Assembler: assembles human-readable assembly code to binary<br>
    &emsp; 2) SPU: execute machine code <br>
    &emsp; 3) DisAssembler: disassembles machine code to human-readable assembly code<br>
<br>
About basic functions in "assembler": <br>
&emsp; 1) <pre><code> PUSH < RAM | REG | NUM > </code> -- add argument with type specified in parentheses</pre> <br>
&emsp; 2) <pre><code> IN </code>                       -- read from input the number  and add it to stack</pre> <br> 
&emsp; 3) <pre><code> POP < RAM | REG > </code>        -- retrieves an element from the stack adds it to register or RAM</pre> <br>
&emsp; 4) <pre><code> ADD </code>                      -- pops 2 numbers from stack and add their sum to stack</pre> <br>
&emsp; 6) <pre><code> SUB </code>                      -- pops 2 numbers from stack and add their difference to stack</pre> <br>
&emsp; 7) <pre><code> MUL </code>                      -- pops 2 numbers from stack and add their product to stack</pre> <br>
&emsp; 8) <pre><code> DIV </code>                      -- pops 2 numbers from stack and add their quotient to stack</pre> <br>
&emsp; 9) <pre><code> SQRT </code>                     -- pop number from stack and add square root of it</pre> <br>
&emsp; 10) <pre><code> SIN </code>                     -- pop number from stack and add sin(number)</pre> <br>
&emsp; 11) <pre><code> COS </code>                     -- pop number from stack and add cos(number)</pre> <br>
&emsp; 12) <pre><code> OUT </code>                     -- pop number from stack and print it</pre> <br>
&emsp; 13) <pre><code> HLT </code>                     -- exit from program</pre> <br>
&emsp; 14) <pre><code> JMP < LBL > </code>             -- go to line</pre> <br>
&emsp; 15) <pre><code> JA < LBL > </code>              -- pop 2 numbers from stack, if first "<" second, then go to line</pre> <br>
&emsp; 16) <pre><code> JAE < LBL > </code>             -- pop 2 numbers from stack, if first "<=" second, then go to line</pre> <br>
&emsp; 17) <pre><code> JB < LBL > </code>              -- pop 2 numbers from stack, if first "> second, then go to line</pre> <br>
&emsp; 18) <pre><code> JBE < LBL > </code>             -- pop 2 numbers from stack, if first ">=" second, then go to line</pre> <br>
&emsp; 19) <pre><code> JE < LBL > </code>              -- pop 2 numbers from stack, if first "==" second, then go to line</pre> <br>
&emsp; 20) <pre><code> JNE < LBL > </code>             -- pop 2 numbers from stack, if first "!=" second, then go to line</pre> <br>
&emsp; 22) <pre><code> CALL < LBL > </code>            -- go to label, and add the last line to call stack</pre> <br>
&emsp; 23) <pre><code> RET </code>                     -- pop label from stack and go to it</pre> <br>
&emsp; 24) <pre><code> PUTC </code>                    -- pop number from stack and print it such as symbol</pre> <br>
&emsp; 25) <pre><code> SET_PIXEL </code>               -- dyes pixel(rbx, rax) color = RAM[rcx]</pre>  <br>
&emsp; 26) <pre><code> CREATE_WINDOW </code>           -- create window 256 by 256</pre> <br>
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
<h2 align="left"> How to launch and use program?</h2>
    &emsp; 1) write in terminal: <code>git clone https://github.com/Ch1n-ch1nless/Preprocessor.git</code> <br>
    &emsp; 2) go to folder:      <code>cd Preprocessor</code> <br>
    &emsp; 3) write in terminal: <code>make compile</code> <br>
    <br>
    &emsp; The command to run the program, you can find in the section 'Programs' <br>
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
<p align="center"><img src="/Img/moon.png" width = "50%"></p>
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

<h1 align = "center"> Thank you for reading! </h1>
<h4 align = "center"> If you have any questions, write on <a href="https://t.me/Chin_chinless" target="_blank">Telegram</a> </h4>
