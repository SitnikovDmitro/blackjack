#include "gamemodel.h"

Card GameModel::getCardFromDeck()
{
    if (deck.isEmpty()) throw "Empty deck";

    Card result = deck.last();
    deck.removeLast();
    return result;
}


void GameModel::reset()
{
    playerHand.clear();
    dealerHand.clear();
    deck.clear();

    QVector<Card> temp;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            temp.append(Card(j, i));
        }
    }

    //srand())

    while (!temp.isEmpty()) {
        const int position = rand() % temp.length();
        const Card card = temp.at(position);
        temp.removeAt(position);
        deck.append(card);
    }

    for (int i = 0; i < 2; i++) {
        const Card card = getCardFromDeck();
        playerHand.append(card);
    }

    for (int i = 0; i < 2; i++) {
        const Card card = getCardFromDeck();
        dealerHand.append(card);
    }

    finished = false;
    winner = 0;
}

void GameModel::stand()
{
    while(getDealerScore() < 17) {
        const Card card = getCardFromDeck();
        dealerHand.append(card);
    }

    if (getDealerScore() > 21) {
        winner = 1;
        playerCash += playerBet;
    } else {
        if (getDealerScore() > getPlayerScore()) {
            winner = -1;
            playerCash -= playerBet;
        } else if (getDealerScore() < getPlayerScore()) {
            winner = 1;
            playerCash += playerBet;
        } else {
            winner = 0;
        }
    }

    finished = true;
}

void GameModel::hit()
{
    const Card card = getCardFromDeck();
    playerHand.append(card);

    const int score = getPlayerScore();
    if (score > 21) {
        winner = -1;
        playerCash -= playerBet;
        finished = true;
    }
}

bool GameModel::isFinished() const
{
    return finished;
}

int GameModel::getWinner() const
{
    return winner;
}

int GameModel::getPlayerScore() const
{
    int score = 0;
    for (Card card : playerHand) {
        score += card.getPoints(score);
    }
    return score;
}

int GameModel::getDealerScore() const
{
    int score = 0;
    for (Card card : dealerHand) {
        score += card.getPoints(score);
    }
    return score;
}

int GameModel::getPlayerCash() const
{
    return playerCash;
}

int GameModel::getPlayerBet() const
{
    return playerBet;
}

void GameModel::setPlayerBet(const int bet)
{
    if (bet <= 0) throw QString("Bet is negative or equals zero");
    playerBet = bet;
}

QVector<Card> GameModel::getPalyerCards() const
{
    return playerHand;
}

QVector<Card> GameModel::getDealerCards() const
{
    return dealerHand;
}

GameModel& GameModel::getInstance() {
    static GameModel instance;
    return instance;
}

GameModel::GameModel() {
    reset();
}

GameModel::~GameModel() {

}


