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
    long randomSeed = getRandomSeed(argc, argv);
    struct gameState state = makeGameState(randomSeed);
    state.deck[state.whoseTurn][0] = adventurer;

    int beforeTreasureCount = countTreasure(&state);
    cardEffect(adventurer, -1, -1, -1, &state, 0, NULL);
    int afterTreasureCount = countTreasure(&state);

    char message[128];
    sprintf(message, "Treasure count should have gone from %d to %d, but instead was %d.\n",
            beforeTreasureCount, beforeTreasureCount + 2, afterTreasureCount);
    int treasureDifference = afterTreasureCount - beforeTreasureCount;
    myassert(treasureDifference == 2, message);

    checkasserts();

    return 0;
}