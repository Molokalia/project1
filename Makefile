CC = gcc

BIN = info_system.bin

OBJ = main.o program.o teacher.o headmaster.o student.o tools.o menu.o sign.o operation.o readandstore.o

FLAG = -Wall -Werror -DDEBUG

STD = -std=gnu99



all: $(OBJ)

	$(CC) -o $(BIN) $(OBJ)



main.o:main.c program.h

	$(CC) -c main.c



prgram.o:program.c program.h tools.h readandstore.h student.h teacher.h headmaster.h menu.h
	
	$(CC) -c program.c



teacher.o:teacher.c teacher.h tools.h menu.h sign.h readandstore.h operation.h

	$(CC) -c teacher.c



student.o:student.c student.h tools.h menu.h sign.h operation.h readandstore.h

	$(CC) -c student.c



headmaster.o:headmaster.c headmaster.h menu.h tools.h sign.h readandstore.h operation.h

	$(CC) -c headmaster.c



tools.o:tools.c tools.h readandstore.h operation.h

	$(CC) -c tools.c



menu.o:menu.c menu.h 

	$(CC) -c menu.c



sign.o:sign.c sign.h tools.h

	$(CC) -c sign.c



operation.o:operation.c operation.h tools.h readandstore.h

	$(CC) -c operation.c



readandstore.o:readandstore.c readandstore.h tools.h student.h teacher.h headmaster.h

	$(CC) -c readandstore.c



clean :

	rm -rf $(BIN) $(OBJ)
