<h1 align="center">PREPROCESSOR</h1>
<h2 align="left">Description</h2>
My realization of working soft processing unit. What this project can do?<br>
    1) This project can translate assembler code to machine code. Code, which does it, locates in folder "Assembler"<br>
    2) Execute machine code. Code, which does it, locates in folder "SPU" <br>
    3) Translate from machine code to assembler code. Code, which does it, locates in folder "DisAssembler"<br>
<br>
The project supports DSL. You can add new commands!!! What you need to do: <br>
    1) Open in folder "DSL" file "commands.dsl" <br>
    2) Write in the end of file: <code>DEF_CMD(...)</code> <br>
        2.1) In brackets you need write: <br>
                name of command <br>
                number of command <br>
                type of arguments <br>
                number of arguments (now better to write 0 or 1, if you write more, can be errors in program) <br>
                action, what program needs to do <br>
<br>
