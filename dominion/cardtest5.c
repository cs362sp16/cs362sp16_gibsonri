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

    state.deckCount[0] = 20;
    memset(state.deck[0], sea_hag, sizeof(state.deck[0]));
    state.deck[0][0] = gardens;

    state.handCount[0] = 20;
    memset(state.hand[0], sea_hag, sizeof(state.hand[0]));

    state.discardCount[0] = 20;
    memset(state.discard[0], sea_hag, sizeof(state.discard[0]));

    int expectedScore = 2;
    int actualScore = scoreFor(0, &state);

    char buf[128];
    sprintf(buf, "Expected score: %d. Actual score: %d.\n", expectedScore, actualScore);
    myassert(expectedScore == actualScore, buf);
    checkasserts();

    return 0;
}
