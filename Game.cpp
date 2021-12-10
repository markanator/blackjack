//
// Created by Mark on 12/8/2021.
//
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "Game.h"
#include "Card.h"

// constants
static char PLAYER_KEY = 'P';
static char DEALER_KEY = 'D';

// using scope resolution modifier
// constructor
Game::Game() { }

// base house deck size
int Game::numCards = 52;

// all cards in the game
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
    // max number converted to double
    static double numB = (double) RAND_MAX + 1.0;
    // random number
    double numA = (double) rand()/numB;
    // gets rando num between 1 to length arg
    return (int)len * numA + 1;
}

void Game::shuffle() {
    // set number of cards back to normal
    // prevents segmentation fault
    Game::numCards = 52;
}

// simple card swap method
void Game::swapCards(int x, int y) {
    Card * temp = gameDeck[x];
    gameDeck[x] = gameDeck[y];
    gameDeck[y] = temp;
}

// return total card count for X Entity
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

// deal cards to entity
void Game::deal(int amount, char plyr) {
    // position that will be used through func
    int posA;
    if (plyr == PLAYER_KEY) {
        // marks end of player hand for gameplay
        playerHand[handSize(PLAYER_KEY) + amount] = NULL;
        // loop to work down amount to zero
        while(amount) {
            // (pre-)decrement and get result
            int newHandIndex = --amount + handSize(PLAYER_KEY);
            // rng position from current deck length
            posA = getRandomNum(numCards);
            // assign houseDeck card to playerhand position
            playerHand[newHandIndex] = gameDeck[posA];
            // swap cards
            swapCards(posA, numCards--);
        }
    }
    else {
        // marks end of player hand for gameplay
        dealerHand[handSize(DEALER_KEY) + amount] = NULL;
        // loop to work down amount to zero
        while(amount) {
            // (pre-)decrement and get result
            int newHandIndex = --amount + handSize(DEALER_KEY);
            // rng position from current deck length
            posA = getRandomNum(numCards);
            // assign houseDeck card to playerhand position
            dealerHand[newHandIndex] = gameDeck[posA];
            // swap cards
            swapCards(posA, numCards--);
        }
    }
}

// returns gameValue of current hand for x player
int Game::handValue(char plyr) {
    // card type
    char cardType;
    // shared counters
    int handVal = 0, aceCount = 0, idx = 0;
    if (plyr == PLAYER_KEY) {
        while (playerHand[idx++]) {
            // get first char of string
            cardType = playerHand[idx - 1]->cardValue[0];
            // award points
            if (cardType == '1' ||
                cardType == 'J' ||
                cardType == 'Q' ||
                cardType == 'K'
            ) {
                handVal += 10;
            }
            // aceCounter... nice!?
            if (cardType == 'A') {
                handVal += 11;
                ++aceCount;
            }
            // catch all other numbers
            if (isdigit(cardType) && (cardType != '1')) {
                handVal += (cardType - '0');
            }
        }
        // subtract aces from count
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
            cardType = dealerHand[idx - 1]->cardValue[0];
            // award points
            if (cardType == '1' ||
                cardType == 'J' ||
                cardType == 'Q' ||
                cardType == 'K'
            ) {
                handVal += 10;
            }
            // aceCounter... nice!?
            if (cardType == 'A') {
                handVal += 11;
                ++aceCount;
            }
            // catch all other numbers
            if (isdigit(cardType) && (cardType != '1')) {
                handVal += (cardType - '0');
            }
        }
        // subtract aces from count
        while (aceCount--) {
            if (handVal > 21) {
                handVal -= 10;
            }
        }
        return handVal;
    }
}

// deal a card to x player
void Game::addToHand(char plyr) {
    deal(1, plyr);
}
