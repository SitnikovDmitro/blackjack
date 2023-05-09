#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QVector>
#include "card.h"

class GameModel
{
private:
    QVector<Card> deck;
    QVector<Card> playerHand;
    QVector<Card> dealerHand;
    bool finished = true;
    int winner = 0;
    int playerCash = 100;
    int playerBet = 10;

    Card getCardFromDeck();

    GameModel();
    ~GameModel();
    GameModel(const GameModel&) = delete;
    GameModel& operator=(const GameModel&) = delete;
public:
    void reset();
    void stand();
    void hit();
    bool isFinished() const;
    int getWinner() const;
    int getPlayerScore() const;
    int getDealerScore() const;
    int getPlayerCash() const;
    int getPlayerBet() const;
    void setPlayerBet(const int bet);
    QVector<Card> getPalyerCards() const;
    QVector<Card> getDealerCards() const;

    static GameModel& getInstance();
};

#endif // GAMEMODEL_H
