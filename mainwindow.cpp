#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamemodel.h"
#include "audio.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->betLineEdit->setValidator(new QIntValidator(1, 100, this));
    reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    if (GameModel::getInstance().isFinished()) {
        ui->hitButton->setVisible(false);
        ui->standButton->setVisible(false);
        ui->returnButton->setVisible(true);

        if (GameModel::getInstance().getWinner() == 1) {
            ui->gameResultLabel->setText(QString("You win ") + QString::number(GameModel::getInstance().getPlayerBet()) + "$");
        } else if (GameModel::getInstance().getWinner() == -1) {
            ui->gameResultLabel->setText(QString("You lose ") + QString::number(GameModel::getInstance().getPlayerBet()) + "$");
        } else {
            ui->gameResultLabel->setText(QString("No one wins"));
        }
    } else {
        ui->hitButton->setVisible(true);
        ui->standButton->setVisible(true);
        ui->returnButton->setVisible(false);
        ui->gameResultLabel->setText("");
    }

    ui->betLabel->setText(QString("Cash: ") + QString::number(GameModel::getInstance().getPlayerCash()) + "$, bet: " + QString::number(GameModel::getInstance().getPlayerBet()) + "$");
    ui->dealerScoreLabel->setText(QString("Dealer's score: ") + QString::number(GameModel::getInstance().getDealerScore()));
    ui->playerScoreLabel->setText(QString("Youy score: ") + QString::number(GameModel::getInstance().getPlayerScore()));
}


void MainWindow::on_standButton_clicked()
{
    int cash = GameModel::getInstance().getPlayerCash();
    int bet = GameModel::getInstance().getPlayerBet();

    GameModel::getInstance().stand();
    ui->canvas->onStand();
    reset();

    Audio::getInstance().playCardSound();

    int winner = GameModel::getInstance().getWinner();

    if (GameModel::getInstance().isFinished()) {
        ui->currentCashLabel->setText(QString("Current cash: %1$").arg(GameModel::getInstance().getPlayerCash()));
        QString str = QString("Cash: %1$, bet: %2$, result: %3").arg(cash).arg(bet).arg(winner == 1 ? "win" : winner == -1 ? "lose" : "draw");
        ui->historyListWidget->addItem(str);
    }
}


void MainWindow::on_hitButton_clicked()
{
    int cash = GameModel::getInstance().getPlayerCash();
    int bet = GameModel::getInstance().getPlayerBet();

    GameModel::getInstance().hit();
    ui->canvas->onHit();
    reset();

    Audio::getInstance().playCardSound();

    int winner = GameModel::getInstance().getWinner();

    if (GameModel::getInstance().isFinished()) {
        ui->currentCashLabel->setText(QString("Current cash: %1$").arg(GameModel::getInstance().getPlayerCash()));
        QString str = QString("Cash: %1$, bet: %2$, result: %3").arg(cash).arg(bet).arg(winner == 1 ? "win" : winner == -1 ? "lose" : "draw");
        ui->historyListWidget->addItem(str);
    }
}




void MainWindow::on_playButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
}


void MainWindow::on_optionsButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->optionsPage);
}


void MainWindow::on_exitButton_clicked()
{
    QCoreApplication::quit();
}


void MainWindow::on_returnButton_clicked()
{
     GameModel::getInstance().reset();
     ui->stackedWidget->setCurrentWidget(ui->gamePage);
     ui->betLineEdit->setValidator(new QIntValidator(1, GameModel::getInstance().getPlayerCash(), this));
     reset();
}


void MainWindow::on_startButton_clicked()
{
    bool valid;
    const int bet = ui->betLineEdit->text().toInt(&valid);
    if (valid && bet >= 1 && bet <= GameModel::getInstance().getPlayerCash()) {
        GameModel::getInstance().setPlayerBet(bet);
        ui->stackedWidget->setCurrentWidget(ui->stepPage);
        reset();
    }
}


void MainWindow::on_returnGameButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}


void MainWindow::on_returnOptionsButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

QString generateStyleSheet(int textureIndex, bool isActive) {
    QString str = QString()
            .append("border: 5px solid;")
            .append("border-radius: 15px;")
            .append("max-width: 100px;")
            .append("max-height: 100px;")
            .append("min-width: 100px;")
            .append("min-height: 100px;")
            .append("background-image: url(:/images/card-back-%1.png);").arg(textureIndex)
            .append(isActive ? "border-color: #008b00;\n" : "border-color: #8b0000;");

    qDebug() << str << "\n";

    return str;
}


void MainWindow::on_cardBack1SelectButton_clicked()
{
    ui->cardBack1SelectButton->setStyleSheet(generateStyleSheet(1,true));
    ui->cardBack2SelectButton->setStyleSheet(generateStyleSheet(2,false));
    ui->cardBack3SelectButton->setStyleSheet(generateStyleSheet(3,false));
    ui->canvas->setCardBackTexture(QImage(":/images/card-back-1.png"));
}


void MainWindow::on_cardBack2SelectButton_clicked()
{
    ui->cardBack1SelectButton->setStyleSheet(generateStyleSheet(1,false));
    ui->cardBack2SelectButton->setStyleSheet(generateStyleSheet(2,true));
    ui->cardBack3SelectButton->setStyleSheet(generateStyleSheet(3,false));
    ui->canvas->setCardBackTexture(QImage(":/images/card-back-2.png"));
}


void MainWindow::on_cardBack3SelectButton_clicked()
{
    ui->cardBack1SelectButton->setStyleSheet(generateStyleSheet(1,false));
    ui->cardBack2SelectButton->setStyleSheet(generateStyleSheet(2,false));
    ui->cardBack3SelectButton->setStyleSheet(generateStyleSheet(3,true));
    ui->canvas->setCardBackTexture(QImage(":/images/card-back-3.png"));
}


QString generateStartButtonStyleSheet(bool isEnabled) {


    QString str = QString()
            .append("border-radius: 15px;")
            .append("border: 5px solid;")
            .append("padding: 10px;")
            .append("padding: 10px;")
            .append(isEnabled ? "background-color: #35BBCA;" : "background-color: #5A5A5A;")
            .append(isEnabled ? "border-color: #0191B4;" : "border-color: #2C2C2C;")
            .append("color: #FFFFFF;")
            .append("font: 24pt \"Berlin Sans FB\";");

    qDebug() << str << "\n";

    return str;
}


void MainWindow::on_betLineEdit_textEdited(const QString &arg1)
{
    bool valid;
    const int bet = ui->betLineEdit->text().toInt(&valid);

    if (valid && bet >= 1 && bet <= GameModel::getInstance().getPlayerCash()) {
        ui->startButton->setStyleSheet(generateStartButtonStyleSheet(true));
    } else {
        ui->startButton->setStyleSheet(generateStartButtonStyleSheet(false));
    }
}


void MainWindow::on_soundButton_clicked()
{
    Audio::getInstance().setSoundEnabled(!Audio::getInstance().isSoundEnabled());
    ui->soundButton->setText(Audio::getInstance().isSoundEnabled() ? "Sound: ON" : "Sound: OFF");
}

