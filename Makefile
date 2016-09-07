OBJS = stockitem.o stocksystem.o a3gradingdriver.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

a3test : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o a3test

stockitem.o : stockitem.h stockitem.cpp
	$(CC) $(CFLAGS) stockitem.cpp -o stockitem.o

stocksystem.o : stocksystem.h stocksystem.cpp stockitem.o rbtree.h rbtreeprivate.h rbtree.cpp
	$(CC) $(CFLAGS) stocksystem.cpp -o stocksystem.o

a3gradingdriver.o : rbtree.h rbtreeprivate.h rbtree.cpp a3gradingdriver.cpp
	$(CC) $(CFLAGS) a3gradingdriver.cpp -o a3gradingdriver.o

clean :
	rm -f *.o *~ a3test
