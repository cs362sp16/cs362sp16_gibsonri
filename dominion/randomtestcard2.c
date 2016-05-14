//
// Created by Rikki Gibson on 5/13/16.
//

#include <stdio.h>
#include "testutils.c"
#include "dominion_helpers.h"
int main(int argc, char **argv) {
    long randomSeed = getRandomSeed(argc, argv);
    struct gameState state = makeGameState(randomSeed);
    state.deck[state.whoseTurn][0] = salvager;

    int cardToGetPos = (int)floor(Random() * state.handCount[state.whoseTurn]);
    int beforeNumBuys = state.numBuys;
    int beforeCoins = state.coins;
    int beforeHandSize = state.handCount[state.whoseTurn];
    cardEffect(salvager, cardToGetPos, -1, -1, &state, 0, NULL);

    myassert(beforeNumBuys + 1 == state.numBuys, "NumBuys didn't increase by 1.");
    myassert(state.coins >= beforeCoins, "Number of coins decreased.");
    if (cardToGetPos) {
        myassert(beforeHandSize - state.handCount[state.whoseTurn] == 2,
                 "Didn't discard 2 cards as expected.");
    } else {
        myassert(beforeHandSize - state.handCount[state.whoseTurn] == 1,
                 "Didn't discard 1 card as expected.");
    }

    checkasserts();
    return 0;
}
