CC=gcc
CFLAGS=-g
LIBS=-lpthread -L ./CommandParser -lcli
TARGET=test.exe

OBJS=gluethread/glthread.o \
     	graph.o		   \
	net.o		   \
	utils.o		   \
	nwcli.o
	#topologies.o

test.exe:testapp.o ${OBJS} CommandParser/libcli.a
	${CC} ${CFLAGS} testapp.o ${OBJS} -o test.exe ${LIBS}

testapp.o:testapp.c
	${CC} ${CFLAGS} -c testapp.c -o testapp.o

gluethread/glthread.o:gluethread/glthread.c
	${CC} ${CFLAGS} -c -I  gluethread gluethread/glthread.c -o gluethread/glthread.o

graph.o:graph.c
	${CC} ${CFLAGS} -c -I . graph.c -o graph.o

net.o:net.c
	${CC} ${CFLAGS} -c -I . net.c -o net.o

utils.o:utils.c
	${CC} ${CFLAGS} -c -I . utils.c -o utils.o

nwcli.o:nwcli.c
	${CC} ${CFLAGS} -c -I . nwcli.c -o nwcli.o

CommandParser/libcli.a:
	(cd CommandParser; make)

clean:
	rm *.o
	rm gluethread/glthread.o
	rm *exe
	(cd CommandParser; make clean)
all:
	make
	(cd CommandParser; make)
