#include <stdio.h>
#include <memory.h>
#include "dominion_helpers.h"

int failed = 0;

void myassert(int b, char* msg)
{
    if (b == 0)
    {
        printf("FAILED ASSERTION: %s\n",msg);
        failed = 1;
    }
}

void checkasserts()
{
    if (!failed)
    {
        printf ("TEST SUCCESSFULLY COMPLETED.\n");
    }
}

int main(int argc, char **argv)
{
    struct gameState state;
    memset(&state, 0, sizeof(struct gameState));

    state.numPlayers = 1;

    state.deckCount[0] = 3;
    state.deck[0][0] = province;
    state.deck[0][1] = duchy;
    state.deck[0][1] = cutpurse;

    state.handCount[0] = 5;
    state.hand[0][0] = treasure_map;
    state.hand[0][1] = province;
    state.hand[0][2] = treasure_map;
    state.hand[0][3] = estate;
    state.hand[0][4] = feast;

    state.discardCount[0] = 5;
    state.discard[0][0] = estate;
    state.discard[0][1] = feast;
    state.discard[0][2] = cutpurse;
    state.discard[0][3] = feast;
    state.discard[0][4] = feast;

    cardEffect(treasure_map, -1, -1, -1, &state, 0, NULL);

    myassert(state.handCount[0] == 7, "Player 2 should have 2 extra cards");
    myassert(state.discardCount[0] == 7, "Should have discarded both treasure maps");
    checkasserts();

    return 0;
}
