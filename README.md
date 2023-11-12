<h1 align="center">PREPROCESSOR</h1>
<h2 align="left">Description</h2>
My realization of working soft processing unit. What this project can do?<br>
    &emsp; 1) This project can translate assembler code to machine code. Code, which does it, locates in folder "Assembler"<br>
    &emsp; 2) Execute machine code. Code, which does it, locates in folder "SPU" <br>
    &emsp; 3) Translate from machine code to assembler code. Code, which does it, locates in folder "DisAssembler"<br>
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
<h2 align="left">Programs</h2>
Examples of programs that are written in "assembly" you can find in folder "Programs" <br>
What programs you can find? <br>
<h4 align="center">Factorial</h4>
&emsp; <code>Brief:</code> &emsp; This program on input takes number and returns it factorial <br> 
<br>
&emsp; <code>Example of working:</code> &emsp; <br>
<p align="center"><img src="/Img/factorial.png" width = "70%"></p>
<br>
<h4 align="center">Fibonacci</h4>

&emsp; <code>Example of working:</code> &emsp; <br>
<p align="center"><img src="/Img/fibonacci.png" width = "70%"></p>
<br>
<h4 align="center">Moon</h4>
&emsp; <code>Brief:</code> &emsp; This program draws beatiful moon <br> 
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
&emsp; <code>Example of working:</code> &emsp; <br>
<p align="center"><img src="/Img/square_equation.png" width = "70%"></p>
