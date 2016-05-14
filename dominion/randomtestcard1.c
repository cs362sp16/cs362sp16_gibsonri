//
// Created by Rikki Gibson on 5/13/16.
//

#include <stdio.h>
#include "testutils.c"
#include "dominion_helpers.h"
#define max(a, b) (((a) > (b)) ? (a) : (b))

int main(int argc, char **argv) {
    long randomSeed = getRandomSeed(argc, argv);
    struct gameState state = makeGameState(randomSeed);
    state.deck[state.whoseTurn][0] = smithy;

    int beforeHandCount = state.handCount[state.whoseTurn];
    int beforeDeckCount = state.deckCount[state.whoseTurn];
    int beforePlayedCount = state.playedCardCount;
    cardEffect(smithy, -1, -1, -1, &state, 0, NULL);

    char message[128];

    sprintf(message, "Hand count should have increased from %d to %d, but instead was %d.",
            beforeHandCount, beforeHandCount + 2, state.handCount[state.whoseTurn]);
    myassert(state.handCount[state.whoseTurn] - beforeHandCount == 2, message);

    sprintf(message, "Deck count should have changed from %d to %d, but instead was %d.",
            beforeDeckCount, max(0, beforeDeckCount- 3), state.deckCount[state.whoseTurn]);
    myassert(state.handCount[state.whoseTurn] - beforeHandCount == 2, message);

    sprintf(message, "Played card count should have changed from %d to %d, but instead was %d.",
            beforePlayedCount, beforePlayedCount + 1, state.playedCardCount);
    myassert(beforePlayedCount + 1 == state.playedCardCount, message);

    checkasserts();
    return 0;
}
