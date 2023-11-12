CC=g++
CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal\
       -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
       -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions\
	   -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security\
	   -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor\
	   -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing\
	   -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla\
	   -D_DEBUG -D_EJUDGE_CLIENT_SIDE -DWITH_CANARY -DWITH_HASH -DWITH_PROC_DUMP

STK_OBJ_DIR = ./Stack/object/
STK_SRC_DIR = ./Stack/source/

SPU_OBJ_DIR = ./SPU/object/
SPU_SRC_DIR = ./SPU/source/

ASM_OBJ_DIR = ./Assembler/object/
ASM_SRC_DIR = ./Assembler/source/

ONG_OBJ_DIR = ./Onegin/object/
ONG_SRC_DIR = ./Onegin/source/

DIS_OBJ_DIR = ./DisAssembler/object/
DIS_SRC_DIR = ./DisAssembler/source/

DIS_SRC = $(wildcard $(DIS_SRC_DIR)*.cpp)
DIS_OBJ = $(patsubst $(DIS_SRC_DIR)%.cpp, $(DIS_OBJ_DIR)%.o, $(DIS_SRC))

STK_SRC = $(wildcard $(STK_SRC_DIR)*.cpp)
STK_OBJ = $(patsubst $(STK_SRC_DIR)%.cpp, $(STK_OBJ_DIR)%.o, $(STK_SRC))

SPU_SRC = $(wildcard $(SPU_SRC_DIR)*.cpp)
SPU_OBJ = $(patsubst $(SPU_SRC_DIR)%.cpp, $(SPU_OBJ_DIR)%.o, $(SPU_SRC))

ASM_SRC = $(wildcard $(ASM_SRC_DIR)*.cpp)
ASM_OBJ = $(patsubst $(ASM_SRC_DIR)%.cpp, $(ASM_OBJ_DIR)%.o, $(ASM_SRC))

ONG_SRC = $(wildcard $(ONG_SRC_DIR)*.cpp)
ONG_OBJ = $(patsubst $(ONG_SRC_DIR)%.cpp, $(ONG_OBJ_DIR)%.o, $(ONG_SRC))

all: asm_compile spu_compile dis_compile run_asm run_spu run_dis

asm_compile: $(ONG_OBJ) $(ASM_OBJ)
	$(CC) $(ASM_OBJ) $(ONG_OBJ) -o asm

$(ONG_OBJ_DIR)%.o : $(ONG_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(ASM_OBJ_DIR)%.o : $(ASM_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

spu_compile: $(STK_OBJ) $(SPU_OBJ)
	$(CC) $(STK_OBJ) $(SPU_OBJ) -o spu

$(STK_OBJ_DIR)%.o : $(STK_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(SPU_OBJ_DIR)%.o : $(SPU_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

dis_compile: $(ONG_OBJ) $(DIS_OBJ)
	$(CC) $(DIS_OBJ) $(ONG_OBJ) -o dis

$(ONG_OBJ_DIR)%.o : $(ONG_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIS_OBJ_DIR)%.o : $(DIS_SRC_DIR)%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

run_asm: 
	./asm Programs/moon.asm Programs/commands.bin

run_spu: 
	./spu Programs/commands.bin

run_dis: 
	./dis Programs/commands.bin Programs/commands.dis

clean:
	rm $(STK_OBJ) $(ASM_OBJ) $(SPU_OBJ) $(DIS_OBJ) $(ONG_OBJ)

