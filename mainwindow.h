#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void reset();

private slots:
    void on_standButton_clicked();

    void on_hitButton_clicked();

    void on_playButton_clicked();

    void on_optionsButton_clicked();

    void on_exitButton_clicked();

    void on_returnButton_clicked();

    void on_startButton_clicked();

    void on_returnGameButton_clicked();

    void on_returnOptionsButton_clicked();

    void on_cardBack1SelectButton_clicked();

    void on_cardBack2SelectButton_clicked();

    void on_cardBack3SelectButton_clicked();

    void on_betLineEdit_textEdited(const QString &arg1);

    void on_soundButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
