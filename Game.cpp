//
// Created by Mark on 12/8/2021.
//
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "Game.h"
#include "Card.h"


static char PLAYER_KEY = 'P';
static char DEALER_KEY = 'D';

// scope resolution modifier
Game::Game() { }
int Game::numCards = 52;
Card *Game::gameDeck[] = { NULL,
   new Card("A",'C'), new Card("A",'D'), new Card("A",'H'), new Card("A",'S'),
   new Card("2",'C'), new Card ("2",'D'), new Card("2",'H'), new Card("2",'S'),
   new Card("3",'C'), new Card ("3",'D'), new Card("3",'H'), new Card("3",'S'),
   new Card("4",'C'), new Card ("4",'D'), new Card("4",'H'), new Card("4",'S'),
   new Card("5",'C'), new Card ("5",'D'), new Card("5",'H'), new Card("5",'S'),
   new Card("6",'C'), new Card ("6",'D'), new Card("6",'H'), new Card("6",'S'),
   new Card("7",'C'), new Card ("7",'D'), new Card("7",'H'), new Card("7",'S'),
   new Card("8",'C'), new Card ("8",'D'), new Card("8",'H'), new Card("8",'S'),
   new Card("9",'C'), new Card ("9",'D'), new Card("9",'H'), new Card("9",'S'),
   new Card("10",'C'),new Card ("10",'D'),new Card("10",'H'),new Card("10",'S'),
   new Card("J",'C'), new Card ("J",'D'), new Card("J",'H'), new Card("J",'S'),
   new Card("Q",'C'), new Card ("Q",'D'), new Card("Q",'H'), new Card("Q",'S'),
   new Card("K",'C'), new Card ("K",'D'), new Card("K",'H'), new Card("K",'S')
};
// create empty hands
Card *Game::dealerHand[53];
Card *Game::playerHand[53];
// ** MAIN METHODS ** //
void Game::start() {
//    initialize random seed
    srand (time(NULL));
    shuffle();
    clearHand();
}
int Game::getRandomNum(int len) {
    double numA;
    static double numB = (double) RAND_MAX + 1.0;
    numA = (double) rand()/numB;
    // gets rando num between 1 to length arg
    return (int)len * numA + 1;
}
void Game::shuffle() {
    // set number of cards back to normal
    Game::numCards = 52;
}
void Game::swapCards(int x, int y) {
    Card * temp = gameDeck[x];
    gameDeck[x] = gameDeck[y];
    gameDeck[y] = temp;
}
int Game::handSize(char plyr) {
    int cardCounter = 0;
    if (plyr == PLAYER_KEY) {
        while(playerHand[cardCounter]) {
            cardCounter++;
        }
    }
    else {
        while(dealerHand[cardCounter]) {
            cardCounter++;
        }
    }

    return cardCounter;
}
void Game::deal(int amount, char plyr) {
    int posA;
    if (plyr == PLAYER_KEY) {
        playerHand[handSize(PLAYER_KEY) + amount] = NULL;
        while(amount) {
            // pre-decrement to get result
            int newHandIndex = --amount + handSize(PLAYER_KEY);
            int rngDeckCardIndex = posA = getRandomNum(numCards);
            playerHand[newHandIndex] = gameDeck[rngDeckCardIndex];
            swapCards(posA, numCards--);
        }
    }
    else {
        dealerHand[handSize(DEALER_KEY) + amount] = NULL;
        while(amount) {
            // pre-decrement to get result
            int newHandIndex = --amount + handSize(DEALER_KEY);
            int rngDeckCardIndex = posA = getRandomNum(numCards);
            dealerHand[newHandIndex] = gameDeck[rngDeckCardIndex];
            swapCards(posA, numCards--);
        }
    }
}
int Game::handValue(char plyr) {
    char type;
    int handVal = 0, aceCount = 0, idx = 0;
    if (plyr == PLAYER_KEY) {
        while (playerHand[idx++]) {
            // get first char of string
            type = playerHand[idx - 1]->cardValue[0];
            if (type == '1' || type == 'J' || type == 'Q' || type == 'K') {
                // award points
                handVal += 10;
            }
            if (type == 'A') {
                // aceCounter... nice!
                handVal += 11;
                ++aceCount;
            }
            if (isdigit(type) && (type != '1')) {
                // catch edge case
                handVal += (type - '0');
            }
        }
        while (aceCount--) {
            if (handVal > 21) {
                handVal -= 10;
            }
        }
        return handVal;
    }
    else {
        while (dealerHand[idx++]) {
            // get first char of string
            type = dealerHand[idx - 1]->cardValue[0];
            if (type == '1' || type == 'J' || type == 'Q' || type == 'K') {
                // award points
                handVal += 10;
            }
            if (type == 'A') {
                // aceCounter... nice!
                handVal += 11;
                ++aceCount;
            }
            if (isdigit(type) && (type != '1')) {
                // catch edge case
                handVal += (type -'0');
            }
        }
        while (aceCount--) {
            if (handVal > 21) {
                handVal -= 10;
            }
        }
        return handVal;
    }
}
void Game::addToHand(char plyr) {
    deal(1, plyr);
}
