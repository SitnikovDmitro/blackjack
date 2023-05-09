#include "canvas.h"
#include "gamemodel.h"
#include "constants.h"
#include <QTimer>






Canvas::Canvas(QWidget *parent) : QWidget(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Canvas::updatePosition);
    timer->start(20);
}

void Canvas::updatePosition() {
    timeElapsed -= 4;
    if (timeElapsed < 0) timeElapsed = 0;

    update();
}

void Canvas::paintEvent(QPaintEvent *event) {
    render();
}

void Canvas::drawCardFront(Card card, int x, int y) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);

    QRect fragmentRect(card.getRank()*134, card.getSuit()*202, 134, 202);
    painter.drawImage(QPoint(x, y), cardsFrontTexture, fragmentRect);

    int width = Constants::CARD_WIDTH;
    int height = Constants::CARD_HEIGHT;
    painter.drawRoundedRect(x, y, width, height, 10, 10);
}

void Canvas::drawCardBack(int x, int y)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);

    painter.drawImage(QPoint(x, y), cardBackTexture);

    int width = Constants::CARD_WIDTH;
    int height = Constants::CARD_HEIGHT;
    painter.drawRoundedRect(x, y, width, height, 10, 10);
}

void Canvas::render() {
    QVector<Card> playerCards = GameModel::getInstance().getPalyerCards();
    QVector<Card> dealerCards = GameModel::getInstance().getDealerCards();

    const int cardWidth = Constants::CARD_WIDTH;
    const int cardHeight = Constants::CARD_HEIGHT;
    const int shift = Constants::CARD_SHIFT;
    const int padding = Constants::CARD_PADDING;
    const int deckX = width()/2 - cardWidth/2;
    const int deckY = padding;

    drawCardBack(deckX, deckY);


    for (int i = 0; i < playerCards.length(); i++) {
        const int endX = i*shift + padding;
        const int endY = height() - cardHeight - padding;
        const int startX = deckX;
        const int startY = deckY;

        if (i == playerCards.length() - 1 && action) {
            const float interpolation = (timeElapsed / 100.0f);
            const int currX = (int)(startX*interpolation + endX*(1.0f - interpolation));
            const int currY = (int)(startY*interpolation + endY*(1.0f - interpolation));

            drawCardFront(playerCards.at(i), currX, currY);
        } else {
            drawCardFront(playerCards.at(i), endX, endY);
        }
    }

    for (int i = 0; i < dealerCards.length(); i++) {
        int startX = i < 2 ? width() - cardWidth - shift + i*shift - padding : deckX;
        int startY = i < 2 ? height() - cardHeight - padding : deckY;
        int endX = width() - cardWidth - (dealerCards.length() - 1)*shift + i*shift - padding;
        int endY = height() - cardHeight - padding;

        const float interpolation = (timeElapsed / 100.0f);
        const int currX = (int)(startX*interpolation + endX*(1.0f - interpolation));
        const int currY = (int)(startY*interpolation + endY*(1.0f - interpolation));


        if (i == 0 && dealerCards.length() <= 2) {
            drawCardBack(currX, currY);
        } else {
            drawCardFront(dealerCards.at(i), currX, currY);
        }
    }


}

void Canvas::onHit() {
    timeElapsed = 100;
    action = true;
}

void Canvas::onStand() {
    timeElapsed = 100;
    action = false;
}

void Canvas::setCardBackTexture(QImage texture) {
    cardBackTexture = texture;
}
