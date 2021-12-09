//
// Created by Mark on 12/8/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H


class Card {
public:
    char club;
    std::string cardValue;
    Card(std::string _val, char _club);
};


#endif //BLACKJACK_CARD_H
