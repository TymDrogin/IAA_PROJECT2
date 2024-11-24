//
// Created by tim on 11/24/24.
//

#ifndef COMMON_DEFINES_H
#define COMMON_DEFINES_H

// PROGRAM CONFIG
#define CENTS_IN_ONE_EURO 100

#define BASE_COIN_TYPES_NUM 4
enum Coins {
    FIVE_CENTS = 5,
    TEN_CENTS = 10,
    TWENTY_CENTS = 20,
    FIFTY_CENTS = 50,
};
extern const int BASE_COINS[];

#endif //COMMON_DEFINES_H
