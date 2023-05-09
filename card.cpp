#include "card.h"
#include <QString>

Card::Card(const int rank, const int suit): rank(rank), suit(suit) {
    if (rank < 0 || rank >= 13 || suit < 0 || suit > 4) throw QString("Invalid card");
}

int Card::getPoints(const int playerScore) const {
    if (rank >= 1 && rank <= 9) {
        return rank + 1;
    }

    if (rank > 9) {
        return 10;
    }

    if (playerScore + 11 <= 21) {
        return 11;
    } else {
        return 1;
    }
}

int Card::getSuit() const {
    return suit;
}

int Card::getRank() const {
    return rank;
}


