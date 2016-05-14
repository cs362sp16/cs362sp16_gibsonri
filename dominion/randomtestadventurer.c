//
// Created by Rikki Gibson on 5/13/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testutils.c"

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
    state.numPlayers = (int)floor(Random() * MAX_PLAYERS);
    state.whoseTurn = (int)floor(Random() * state.numPlayers);
    return state;
}

int isTreasure(enum CARD c) {
    return c == copper || c == silver || c == gold;
}

int countTreasure(struct gameState *state) {
    int currentPlayer = state->whoseTurn;
    int treasureCount = 0;
    for (int i = 0; i < state->handCount[currentPlayer]; i++) {
        if (isTreasure(state->hand[currentPlayer][i])) {
            treasureCount++;
        }
    }
    return treasureCount;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s randomseed\n", argv[0]);
        return 1;
    }

    char *error = "";
    long randomSeed = strtol(argv[1], &error, 10);
    if (strlen(error) != 0) {
        printf("%s did not parse as a number. randomseed needs to be a number.\n", error);
        printf("Usage: %s randomseed\n", argv[0]);
        return 1;
    }
    struct gameState state = makeGameState(randomSeed);
    state.deck[state.whoseTurn][0] = adventurer;

    int beforeTreasureCount = countTreasure(&state);
    cardEffect(adventurer, -1, -1, -1, &state, 0, NULL);
    int afterTreasureCount = countTreasure(&state);

    char message[128];
    if (beforeTreasureCount == 0) {
        sprintf(message, "Treasure should have stayed at 0, but instead was %d.\n", afterTreasureCount);
        myassert(afterTreasureCount == 0, message);
    }
    else if (beforeTreasureCount == 1) {
        sprintf(message, "Treasure should have gone from 1 to 0, but instead was %d.\n", afterTreasureCount);
        myassert(afterTreasureCount == 0, message);
    } else {
        sprintf(message, "Treasure count should have gone from %d to %d, but instead was %d.\n", beforeTreasureCount, beforeTreasureCount - 2, afterTreasureCount);
        int treasureDifference = afterTreasureCount - beforeTreasureCount;
        myassert(treasureDifference == 2, message);
    }

    checkasserts();

    return 0;
}