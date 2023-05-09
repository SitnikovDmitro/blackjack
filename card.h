#ifndef CARD_H
#define CARD_H


class Card {
private:
    const int rank, suit;
public:
    Card(const int rank, const int suit);
    int getPoints(const int playerScore) const;
    int getSuit() const;
    int getRank() const;
};

#endif // CARD_H
