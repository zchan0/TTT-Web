CC      = g++
C       = cpp
H       = h

CFLAGS  = -g -Wall -Wextra -pedantic
#LDFLAGS = -lm

HFILES  = model/Player.${H} model/Board.${H}
OBJS    = model/Player.o model/Board.o

TARGET = ttt

${TARGET}: ${OBJS} main.o
	${CC} ${CFLAGS} -o ${TARGET} ${OBJS} main.o 

main.o: main.cpp ${HFILES}
	${CC} ${CFLAGS} -c main.cpp

Player.o: model/Player.${C} ${HFILES}
	${CC} ${CFLAGS} -c Player.${C}
	
Board.o: model/Board.${C} ${HFILES}
	${CC} ${CFLAGS} -c Board.${C}

clean:
	rm -rf *.o model/*.o controller/*.o
	rm -rf *~
	rm -rf ${TARGET}
