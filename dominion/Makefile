SHELL = /bin/bash
CFLAGS = -Wall -std=c99 -g -fpic -coverage -lm
CC = gcc

rngs.o: rngs.h rngs.c
	$(CC) -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	$(CC) -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	$(CC) -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	$(CC) -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	$(CC) -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

unittest1: dominion.o rngs.o
	$(CC) -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o rngs.o
	$(CC) -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o rngs.o
	$(CC) -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o rngs.o
	$(CC) -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: dominion.o rngs.o
	$(CC) -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: dominion.o rngs.o
	$(CC) -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: dominion.o rngs.o
	$(CC) -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: dominion.o rngs.o
	$(CC) -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: dominion.o rngs.o
	$(CC) -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: dominion.o rngs.o
	$(CC) -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o rngs.o
	$(CC) -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4
unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4
	unittest1 >> unittestresults.out
	unittest2 >> unittestresults.out
	unittest3 >> unittestresults.out
	unittest4 >> unittestresults.out
	cardtest1 >> unittestresults.out
	cardtest2 >> unittestresults.out
	cardtest3 >> unittestresults.out
	cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out

randomtestcard1.out: randomtestcard1
	./randomtestcard1 42 >> randomtestcard1.out
	-gcov dominion.c >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	./randomtestcard2 42 >> randomtestcard2.out
	-gcov dominion.c >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer 42 >> randomtestadventurer.out
	-gcov dominion.c >> randomtestadventurer.out


testdominion: testdominion.c dominion.o rngs.o interface.o
	$(CC) -o testdominion testdominion.c dominion.o rngs.o interface.o $(CFLAGS)

gtestdominion.out: testdominion
	-gtimeout 5 ./testdominion 42 >> testdominion.out
	-gcov dominion.c >> testdominion.out

testdominion.out: testdominion
	-timeout 5 ./testdominion 42 >> testdominion.out
	-gcov dominion.c >> testdominion.out

mac: CC = gcc-5
mac: playdom player

clean:
	rm -rf *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM *.out
