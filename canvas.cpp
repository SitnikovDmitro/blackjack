#include "canvas.h"
#include "gamemodel.h"
#include <QTimer>






Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
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

void Canvas::drawCardFront(Card card, int x, int y)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);

    QRect fragmentRect(card.getRank()*134, card.getSuit()*202, 134, 202);
    painter.drawImage(QPoint(x, y), cardsFrontTexture, fragmentRect);

    int width = 134;
    int height = 202;
    int radius = 10;
    painter.drawRoundedRect(x, y, width, height, radius, radius);
}

void Canvas::drawCardBack(int x, int y)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);

    painter.drawImage(QPoint(x, y), cardBackTexture);

    int width = 134;
    int height = 202;
    int radius = 10;
    painter.drawRoundedRect(x, y, width, height, radius, radius);
}

void Canvas::render()
{
    QVector<Card> playerCards = GameModel::getInstance().getPalyerCards();
    QVector<Card> dealerCards = GameModel::getInstance().getDealerCards();

    const int cardWidth = 134;
    const int cardHeight = 202;
    const int shift = 20;
    const int padding = 5;
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

        //qDebug("Drawed player: x=%d, y=%d", x, y);
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

void Canvas::onHit()
{
    timeElapsed = 100;
    action = true;
}

void Canvas::onStand()
{
    timeElapsed = 100;
    action = false;
}

void Canvas::setCardBackTexture(QImage texture)
{
    cardBackTexture = texture;
}
