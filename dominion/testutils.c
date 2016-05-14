//
// Created by Rikki Gibson on 5/13/16.
//
#include <stdio.h>
#include "dominion.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rngs.h"

int failed = 0;

void myassert(int b, char* msg)  {
    if (b == 0) {
        printf("FAILED ASSERTION: %s\n",msg);
        failed = 1;
    }
}

void checkasserts() {
    if (!failed) {
        printf ("TEST SUCCESSFULLY COMPLETED.\n");
    }
}

long getRandomSeed(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage: %s randomseed\n", argv[0]);
        exit(1);
    }

    char *error = "";
    long randomSeed = strtol(argv[1], &error, 10);
    if (strlen(error) != 0) {
        printf("%s did not parse as a number. randomseed needs to be a number.\n", error);
        printf("Usage: %s randomseed\n", argv[0]);
        exit(1);
    }
    return randomSeed;
}

enum CARD randomCard() {
    return (enum CARD)(int)floor(Random() * (treasure_map + 1));
}

struct gameState makeGameState(long randomSeed) {
    SelectStream(1);
    PutSeed(randomSeed);

    struct gameState state;
    state.coins = (int)Random();
    for (int i = 0; i < MAX_PLAYERS; i++) {
        for (int j = 0; j < MAX_DECK; j++) {
            state.deck[i][j] = randomCard();
            state.discard[i][j] = randomCard();
            state.hand[i][j] = randomCard();
        }
        for (int j = 0; j < MAX_HAND; j++) {
            state.hand[i][j] = randomCard();
        }
        state.deckCount[i] = (int)floor(Random() * MAX_DECK);
        state.discardCount[i] = (int)floor(Random() * MAX_DECK);
        state.handCount[i] = (int)floor(Random() * MAX_HAND);
    }
    for (int i = 0; i < MAX_DECK; i++) {
        state.playedCards[i] = randomCard();
    }
    state.playedCardCount = (int)floor(Random() * MAX_DECK);
    state.numPlayers = (int)floor(Random() * MAX_PLAYERS);
    state.whoseTurn = (int)floor(Random() * state.numPlayers);
    return state;
}
