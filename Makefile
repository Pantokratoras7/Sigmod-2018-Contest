CC = gcc -Wall -g -pthread
FILES = main.c radixHashJoin.c queryMethods.c relationMethods.c implementation.c threadPool.c
OBJECTS = main.o radixHashJoin.o queryMethods.o relationMethods.o implementation.o threadPool.o
OUT = joinProgram
HEADERS = radixHashJoin.h queryMethods.h relationMethods.h implementation.h threadPool.h

all: $(OBJECTS) $(HEADERS)
	$(CC) -o $(OUT) -lm $(FILES)
	make clean_some

main.o: main.c
	$(CC) -c main.c

radixHashJoin.o: radixHashJoin.c
	$(CC) -c radixHashJoin.c

queryMethods.o: queryMethods.c
	$(CC) -c queryMethods.c

relationMethods.o: relationMethods.c
	$(CC) -c relationMethods.c

implementation.o: implementation.c
	$(CC) -c implementation.c

threadPool.o: threadPool.c
	$(CC) -c threadPool.c

clean_some:
	rm -f $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(OUT)
