// Created by Mark on 12/8/2021.
// tutoring help from: Jesus Ambrocio (my brother)
// and past c# card projects
//

#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// constants
static char PLAYER_KEY = 'P';
static char DEALER_KEY = 'D';

// instance of a game
Game blackjackGame;

// declare funcs
void roundOver();
void playOrHold(bool playOrStayRngBool);
bool randomBool();

// counters to be used in this file
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
            // keep playing or nah
            playOrHold(playOrStayRngBool);
        }

        if (currRound > 5) {
            // prevent segmentation fault when trying to deal, thanks gdb
            blackjackGame.shuffle();
            currRound = 0;
        }
        //
        totGames--;
    }
    // FIXME: win rates are skewed in favor of the house
    printf("\n\nFinal Scores:\n");
    printf("House: %d\n", houseWins);
    printf("Guest: %d\n", playerWins);
    printf("Draws: %d\n\n", drawGameCount);

    return 0;
}

// define funcs

bool randomBool() {
    // should probably make a better random bool method
    return rand() > (RAND_MAX / 2);
}
void playOrHold(bool playOrStayRngBool) {
    if (playOrStayRngBool) {
        // next round
        blackjackGame.addToHand(PLAYER_KEY);
        if (blackjackGame.handValue(PLAYER_KEY) < 21) {
            // keep playing?
            playOrHold(randomBool());
        } else {
            // endgame
            roundOver();
        }
    }
    else {
        // keep playing
        while (blackjackGame.handValue(DEALER_KEY) < 17) {
            blackjackGame.addToHand(DEALER_KEY);
        }
        // endgame
        roundOver();
    }
}

void roundOver() {
    int plyrHV = blackjackGame.handValue(PLAYER_KEY);
    int dlerHV = blackjackGame.handValue(DEALER_KEY);

    // print current party handValues
    printf("Player = %d\n", plyrHV);
    printf("Dealer = %d\n", dlerHV);

    // do some maths to check for winner
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
