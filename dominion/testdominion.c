//
// Created by Rikki Gibson on 5/22/16.
//

#include <stdio.h>
#include <stdbool.h>
#include "dominion.h"
#include "testutils.c"
#include "dominion_helpers.h"

bool cardsContains(enum CARD *cards, enum CARD target, int endIndex) {
    for (int i = 0; i < endIndex; i++) {
        if (cards[i] == target) {
            return true;
        }
    }
    return false;
}

/**
 * Populates an array with random kingdom cards, ensuring no duplicates.
 * This function assumes it is receiving a pointer to 10 cards.
 */
void randomKingdomCards(enum CARD *cards) {
    for (int i = 0; i < 10; i++) {
        cards[i] = randomCard();
        // Keep fetching random cards until it's not a duplicate from earlier in the list
        while (cardsContains(cards, cards[i], i-1)) {
            cards[i] = randomCard();
        }
    }
}

struct gameState initializeRandomGame(long randomSeed) {
    SelectStream(1);
    PutSeed(randomSeed);

    enum CARD kingdomCards[10];
    randomKingdomCards(kingdomCards);

    // get between 2 and 4 players
    int numPlayers = ((int)floor(Random()*2)) + 2;
    struct gameState g;
    initializeGame(numPlayers, (int *)kingdomCards, (int)randomSeed, &g);
    return g;
}

bool isActionCard(enum CARD card) {
    return card >= adventurer && card <= treasure_map;
}

bool containsActionCard(enum CARD *cards, int len) {
    for (int i = 0; i < len; i++) {
        if (isActionCard(cards[i])) {
            return true;
        }
    }
    return false;
}

int getRandomActionCardIndex(struct gameState *g) {
    int handCount = g->handCount[g->whoseTurn];
    enum CARD *currentHand = g->hand[g->whoseTurn];

    if (!containsActionCard(currentHand, handCount)) {
        return -1;
    }

    int randomIndex = (int)floor(Random()*handCount);
    while (!isActionCard(currentHand[randomIndex])) {
        randomIndex = (int)floor(Random()*handCount);
    }
    return randomIndex;
}

int playRandomCard(struct gameState *g) {
    int randomIndex = getRandomActionCardIndex(g);
    enum CARD cardToPlay = g->hand[g->whoseTurn][randomIndex];
    int result = playCard(randomIndex, -1, -1, -1, g);
    printf("Played card %d\n", cardToPlay);
    return result;
}

void doPlayerActionPhase(struct gameState *g) {
    bool success = true;
    while (success && g->numActions > 0 && containsActionCard(g->hand[g->whoseTurn], g->handCount[g->whoseTurn])) {
        success = playRandomCard(g) == -1 ? false : true;
    }
}

bool canBuyCard(struct gameState *g) {
    if (g->numBuys == 0) {
        return false;
    }

    for (int i = 0; i < treasure_map + 1; i++) {
        // Is this card available to buy and we have enough coins?
        if (g->supplyCount[i] != 0 && getCost(i) <= g->coins) {
            return true;
        }
    }
    return false;
}

/**
 * Returns a value indicating whether the card was bought.
 */
bool buyRandomCard(struct gameState *g) {
    if (!canBuyCard(g)) {
        return false;
    }

    // get a card which we can afford, is not a curse, and is in the supply
    enum CARD card = randomCard();
    while (getCost(card) > g->coins || card == curse || g->supplyCount[card] == 0) {
        card = randomCard();
    }
    printf("Buying card %d\n", card);
    return buyCard(card, g) == 0;
}

void doPlayerBuyPhase(struct gameState *g) {
    updateCoins(g->whoseTurn, g, 0);
    while (canBuyCard(g)) {
        if (!buyRandomCard(g)) break;
    }
}

void playRandomGame(long randomSeed) {
    struct gameState g = initializeRandomGame(randomSeed);
    printf("Begin game with %d players\n", g.numPlayers);
    while (!isGameOver(&g)) {
        printf("Begin player %d turn\n", g.whoseTurn);
        doPlayerActionPhase(&g);
        doPlayerBuyPhase(&g);
        endTurn(&g);
    }
    printf("Game over.\n");

    for (int i = 0; i < g.numPlayers; i++) {
        printf("Player %d score: %d\n", i, scoreFor(i, &g));
    }
    int winners[4];
    getWinners(winners, &g);
    for (int i = 0; i < g.numPlayers; i++) {
        if (winners[i]) {
            printf("Player %d won!\n", i);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: testdominion <randomseed>\n");
        return 0;
    }
    long randomSeed = getRandomSeed(argc, argv);
    playRandomGame(randomSeed);

    return 0;
}