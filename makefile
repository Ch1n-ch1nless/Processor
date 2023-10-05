CC=g++
CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal\
       -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
       -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions\
	   -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security\
	   -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor\
	   -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing\
	   -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla\
	   -D_DEBUG -D_EJUDGE_CLIENT_SIDE -DWITH_CANARY -DWITH_HASH 

STK_OBJ_DIR = ./Stack/object/
STK_SRC_DIR = ./Stack/source/

CPU_OBJ_DIR = ./CPU/object/
CPU_SRC_DIR = ./CPU/source/

ASM_OBJ_DIR = ./Assembler/object/
ASM_SRC_DIR = ./Assembler/source/

DIS_OBJ_DIR = ./Disassembler/object/
DIS_SRC_DIR = ./Disassembler/source/

ONG_OBJ_DIR = ./Onegin/object/
ONG_SRC_DIR = ./Onegin/source/

STK_SRC = $(wildcard $(STK_SRC_DIR)*.cpp)
STK_OBJ = $(patsubst $(STK_SRC_DIR)%.cpp, $(STK_OBJ_DIR)%.o, $(STK_SRC))

CPU_SRC = $(wildcard $(CPU_SRC_DIR)*.cpp)
CPU_OBJ = $(patsubst $(CPU_SRC_DIR)%.cpp, $(CPU_OBJ_DIR)%.o, $(CPU_SRC))

ASM_SRC = $(wildcard $(ASM_SRC_DIR)*.cpp)
ASM_OBJ = $(patsubst $(ASM_SRC_DIR)%.cpp, $(ASM_OBJ_DIR)%.o, $(ASM_SRC))

DIS_SRC = $(wildcard $(DIS_SRC_DIR)*.cpp)
DIS_OBJ = $(patsubst $(DIS_SRC_DIR)%.cpp, $(DIS_OBJ_DIR)%.o, $(DIS_SRC))

ONG_SRC = $(wildcard $(ONG_SRC_DIR)*.cpp)
ONG_OBJ = $(patsubst $(ONG_SRC_DIR)%.cpp, $(ONG_OBJ_DIR)%.o, $(ONG_SRC))

all: asm_compile cpu_compile dis_compile run_asm run_cpu run_dis

asm_compile: $(ONG_OBJ) $(ASM_OBJ)
	$(CC) $(ASM_OBJ) $(ONG_OBJ) -o asm

$(ONG_OBJ_DIR)%.o : $(ONG_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(ASM_OBJ_DIR)%.o : $(ASM_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

cpu_compile: $(STK_OBJ) $(CPU_OBJ)
	$(CC) $(STK_OBJ) $(CPU_OBJ) -o cpu

$(STK_OBJ_DIR)%.o : $(STK_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(CPU_OBJ_DIR)%.o : $(CPU_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

dis_compile: $(ONG_OBJ) $(DIS_OBJ)
	$(CC) $(DIS_OBJ) $(ONG_OBJ) -o dis

$(ONG_OBJ_DIR)%.o : $(ONG_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIS_OBJ_DIR)%.o : $(DIS_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

run_asm: 
	./asm

run_cpu: 
	./cpu

run_dis: 
	./dis

clean:
	rm $(STK_OBJ) $(ASM_OBJ) $(CPU_OBJ) $(DIS_OBJ) $(ONG_OBJ)

