CC=gcc
CFLAGS=-g -O0 -Wall -Wextra
LIBS=-lpthread -L ./CommandParser -lcli
TARGET=test.exe

OBJS=gluethread/glthread.o 	\
        Layer2/layer2.o	   	\
	Layer2/l2switch.o	\
     	graph.o		   	\
	topology.o         	\
	net.o		   	\
	utils.o		   	\
	nwcli.o		   	\
	comm.o		
	#topologies.o

test.exe:testapp.o ${OBJS} CommandParser/libcli.a
	${CC} ${CFLAGS} testapp.o ${OBJS} -o test.exe ${LIBS}

testapp.o:testapp.c
	${CC} ${CFLAGS} -c testapp.c -o testapp.o

gluethread/glthread.o:gluethread/glthread.c
	${CC} ${CFLAGS} -c -I  gluethread gluethread/glthread.c -o gluethread/glthread.o

Layer2/layer2.o:Layer2/layer2.c
	${CC} ${CFLAGS} -c -I Layer2 Layer2/layer2.c -o Layer2/layer2.o

Layer2/l2switch.o:Layer2/l2switch.c
	${CC} ${CFLAGS} -c -I Layer2 Layer2/l2switch.c -o Layer2/l2switch.o

graph.o:graph.c
	${CC} ${CFLAGS} -c -I . graph.c -o graph.o

topology.o:topology.c
	${CC} ${CFLAGS} -c -I . topology.c -o topology.o

net.o:net.c
	${CC} ${CFLAGS} -c -I . net.c -o net.o

utils.o:utils.c
	${CC} ${CFLAGS} -c -I . utils.c -o utils.o

nwcli.o:nwcli.c
	${CC} ${CFLAGS} -c -I . nwcli.c -o nwcli.o

comm.o:comm.c
	${CC} ${CFLAGS} -c -I . comm.c -o comm.o

CommandParser/libcli.a:
	(cd CommandParser; make)

clean:
	rm *.o
	rm gluethread/glthread.o
	rm Layer2/*.o
	rm *exe
	(cd CommandParser; make clean)
all:
	make
	(cd CommandParser; make)
