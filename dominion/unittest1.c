#include <stdio.h>
#include <memory.h>
#include "dominion.h"

int failed = 0;

int myassert(int b, char* msg)
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

    state.deckCount[0] = 5;
    state.deck[0][0] = feast;
    state.deck[0][1] = feast;
    state.deck[0][2] = feast;
    state.deck[0][3] = feast;
    state.deck[0][4] = cutpurse;

    state.handCount[0] = 5;
    state.hand[0][0] = cutpurse;
    state.hand[0][1] = feast;
    state.hand[0][2] = feast;
    state.hand[0][3] = feast;
    state.hand[0][4] = feast;

    state.discardCount[0] = 5;
    state.discard[0][0] = feast;
    state.discard[0][1] = feast;
    state.discard[0][2] = cutpurse;
    state.discard[0][3] = feast;
    state.discard[0][4] = feast;

    int count = fullDeckCount(0, feast, &state);
    myassert(count == 12, "Expecting to have 12 feast cards in full deck count");
    checkasserts();
}
