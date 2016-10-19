CC      = g++
C       = cpp
H       = h

CFLAGS  = -g -Wall -Wextra -pedantic
#LDFLAGS = -lm

HFILES  = model/Player.${H} model/Board.${H} model/Json.${H} controller/TTTController.${H}
OBJS    = model/Player.o model/Board.o model/Json.o controller/TTTController.o

TARGET = ttt

${TARGET}: ${OBJS} main.o
	${CC} ${CFLAGS} -o ${TARGET} ${OBJS} main.o 

main.o: main.cpp ${HFILES}
	${CC} ${CFLAGS} -c main.cpp

TTTController.o: controller/TTTController.${C} ${HFILES}
	${CC} ${CFLAGS} -c TTTController.${C}	

Player.o: model/Player.${C} ${HFILES}
	${CC} ${CFLAGS} -c Player.${C}
	
Board.o: model/Board.${C} ${HFILES}
	${CC} ${CFLAGS} -c Board.${C}

Json.o: model/Json.${C} ${HFILES}
	${CC} ${CFLAGS} -c Json.${C}

clean:
	rm -rf *.o 
	rm -rf *~
	rm -rf ${TARGET} ${OBJS}
