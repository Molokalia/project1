CC = gcc
BIN = mail.bin
OBJ = main.o teacher.o headmaster.o student.o tools.o
FLAG = -Wall -Werror -DDEBUG
STD = -std=gnu99

all: $(OBJ)
	$(CC) -o $(BIN) $(OBJ) && ./$(BIN)

%o:%.c
	$(CC) $(STD) $(FLAG) -c $< -o $@

clean :
	rm -rf $(BIN) $(OBJ)
