// Game Class definition
// Created by Mark on 12/8/2021.
//
#include "Card.h"
#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H

class Game {
private:
    int handSize(char plyr);                    // count of cards in hand
    void swapCards(int aPos,int bPos);          // swap cards method
    int getRandomNum(int len);                  // generate random number
    // using static to persist throughout program lifetime
    static Card *gameDeck[53];                  // main game deck
    static Card *dealerHand[53];                // dealer's deck
    static Card *playerHand[53];                // fake players deck
    static int numCards;                        // number of cards in game deck
public:
    Game();                     // constructor
    void start();               // initialize rng
    void shuffle();             // shuffle deck
    void deal(int num, char plyr);  // deal num card to plyr
    int handValue(char plyr);      // will calc plyr hand value
    void addToHand(char plyr);      // adds card to hand
    void clearHand() {          // clears players hand
        dealerHand[0] = NULL;
        playerHand[0] = NULL;
    }
};


#endif //BLACKJACK_GAME_H
