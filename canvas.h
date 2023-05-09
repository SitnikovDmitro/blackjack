#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
//#include <QtMultimedia/QMediaPlayer>
#include <card.h>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void onHit();
    void onStand();
    void setCardBackTexture(QImage texture);
private:
    QImage cardsFrontTexture = QImage(":/images/cards-front.png");
    QImage cardBackTexture = QImage(":/images/card-back-3.png");
   // QMediaPlayer player = QMediaPlayer();
    QTimer* timer;
    bool action = false;
    int timeElapsed = 100;

private slots:
    void updatePosition();

protected:
    void paintEvent(QPaintEvent* event) override;
    void drawCardFront(Card card, int x, int y);
    void drawCardBack(int x, int y);
    void render();

signals:

};

#endif // CANVAS_H
