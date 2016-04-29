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
    int players[MAX_PLAYERS];
    memset(&state, 0, sizeof(struct gameState));
    memset(players, 0, sizeof(int) * MAX_PLAYERS);

    state.numPlayers = 2;

    // Set up player 1 stuff
    state.deckCount[0] = 3;
    state.deck[0][0] = province; // 6
    state.deck[0][1] = duchy; // 3
    state.deck[0][1] = cutpurse;

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

    // Set up player 2 stuff
    state.deckCount[1] = 3;
    state.deck[1][0] = duchy; // 3
    state.deck[1][1] = duchy; // 3
    state.deck[1][1] = cutpurse;

    state.handCount[0] = 5;
    state.hand[1][0] = cutpurse;
    state.hand[1][1] = province; // 6
    state.hand[1][2] = duchy; // 3
    state.hand[1][3] = estate; // 1
    state.hand[1][4] = feast;

    state.discardCount[0] = 5;
    state.discard[1][0] = estate; // 1
    state.discard[1][1] = feast;
    state.discard[1][2] = cutpurse;
    state.discard[1][3] = feast;
    state.discard[1][4] = feast;

    getWinners(players, &state);
    myassert(players[0], "Player 1 should win");
    myassert(!players[1], "Player 2 should lose");
    checkasserts();

    return 0;
}
