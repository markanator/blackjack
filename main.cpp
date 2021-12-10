// Created by Mark on 12/8/2021.
// tutoring help from: Jesus Ambrocio (my brother)
// and past c# card projects
//

#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

static char PLAYER_KEY = 'P';
static char DEALER_KEY = 'D';
Game blackjackGame;
// declare funcs
void roundOver();
void playOrHold(bool playOrStayRngBool);
bool randomBool();

int playerWins=0, houseWins=0, drawGameCount=0, currRound=0, totGames=100;

int main() {
    blackjackGame.start();
    // 100 games
    while(totGames) {
        currRound++;
        bool playOrStayRngBool = randomBool();
        blackjackGame.clearHand();
        blackjackGame.deal(2, DEALER_KEY);
        blackjackGame.deal(2, PLAYER_KEY);
        // check values
        if (blackjackGame.handValue(PLAYER_KEY) >= 21 || blackjackGame.handValue(DEALER_KEY) >= 21) {
            roundOver();
        }
        else {
            playOrHold(playOrStayRngBool);
        }

        if (currRound > 5) {
            // fix segmentation fault when trying to deal
            blackjackGame.shuffle();
            currRound = 0;
        }
        totGames--;
    }
    // win rates are skewed in favor of the house
    printf("\n\nFinal Scores:\n");
    printf("House: %d\n", houseWins);
    printf("Guest: %d\n", playerWins);
    printf("Draws: %d\n\n", drawGameCount);

    return 0;
}

// define funcs

bool randomBool() {
    return rand() > (RAND_MAX / 2);
}
void playOrHold(bool playOrStayRngBool) {
    if (playOrStayRngBool) {
        blackjackGame.addToHand(PLAYER_KEY);
        if (blackjackGame.handValue(PLAYER_KEY) < 21) {
            playOrHold(randomBool());
        } else {
            roundOver();
        }
    }
    else {
        while (blackjackGame.handValue(DEALER_KEY) < 17) {
            blackjackGame.addToHand(DEALER_KEY);
        }
        roundOver();
    }
}
void roundOver() {
    int plyrHV = blackjackGame.handValue(PLAYER_KEY);
    int dlerHV = blackjackGame.handValue(DEALER_KEY);

    printf("Player = %d\n", plyrHV);
    printf("Dealer = %d\n", dlerHV);

    if (plyrHV > 21 || (dlerHV > plyrHV && dlerHV <= 21)) {
        cout << "DEALER WINS!" << endl;
        houseWins++;
    }
    else if (dlerHV > 21 || (plyrHV > dlerHV && plyrHV <= 21)) {
        cout << "PLAYER WINS!" << endl;
        playerWins++;
    } else {
        cout << "TIE!" << endl;
        drawGameCount++;
    }

}
