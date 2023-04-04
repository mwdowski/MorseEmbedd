.PHONY = all clean
#CC=$(CROSS_COMPILE)gcc
CC=gcc
CFLAGS=-Wall -Wno-unknown-pragmas -g3
LIBS := -lgpiod

OBJS := morse.o

main: main.c morse.o
	$(CC) -o main $(CFLAGS) $(LDFLAGS) main.c $(LIBS)

morse.o: morse.h morse.c
	$(CC) -c -o morse.o $(CFLAGS) morse.c 

clean:
	@echo "Cleaning up..."
	rm -rvf *.o ${EXEC_NAME}