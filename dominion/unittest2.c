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

    state.deckCount[0] = 3;
    state.deck[0][0] = province; // 6
    state.deck[0][1] = duchy; // 3
    state.deck[0][2] = cutpurse;

    state.handCount[0] = 5;
    state.hand[0][0] = cutpurse;
    state.hand[0][1] = province; // 6
    state.hand[0][2] = duchy; // 3
    state.hand[0][3] = estate; // 1
    state.hand[0][4] = feast;

    state.discardCount[0] = 5;
    state.discard[0][0] = estate; // 1
    state.discard[0][1] = feast;
    state.discard[0][2] = cutpurse;
    state.discard[0][3] = feast;
    state.discard[0][4] = feast;

    int count = scoreFor(0, &state);
    myassert(count == 20, "Expecting to have 20 score");
    checkasserts();

    return 0;
}
