#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <random>
#include <string>
#include <algorithm>

int curScore = 0;
int remTries = 50;
std::vector<std::string> cards;

QPushButton *buttons[31];
int isPressed[31];

std::string selectedCard = "";
int selectedIndex = -1;
int secondSelectedIndex = -1;
int isCorrect = -1;

std::string pilotNames[15] = {
    "Michael Schumacher", "Lewis Hamilton", "Ayrton Senna", "Juan Manuel Fangio", "Sebastian Vettel",
    "Alain Prost", "Niki Lauda", "Jim Clark", "Jackie Stewart", "Mika Hakkinen",
    "Fernando Alonso", "Nelson Piquet", "Nigel Mansell", "Stirling Moss", "Emerson Fittipaldi"
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->scoreValue->setText(QString::number(curScore));
    ui->triesValue->setText(QString::number(remTries));

    for(int i = 1; i < 31; i++) {
        QString butName = "pushButton_" + QString::number(i);
        buttons[i] = MainWindow::findChild<QPushButton *>(butName);
        buttons[i]->setText("?");
        connect(buttons[i], SIGNAL(released()), this, SLOT(buttonPressed()));
    }

    QPushButton *newGameButton = MainWindow::findChild<QPushButton *>(QString("newGameButton"));
    connect(newGameButton, SIGNAL(released()), this, SLOT(newGamePressed()));

    newGamePressed();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGamePressed() {
    curScore = 0;
    remTries = 50;
    ui->scoreValue->setText(QString::number(curScore));
    ui->triesValue->setText(QString::number(remTries));

    for(int i = 1; i < 31; i++) {
        buttons[i]->setText("?");
        isPressed[i] = -1;
    }

    for(int i = 0; i < 15; i++) {
        for(int j=0; j<2; j++){
            cards.push_back(pilotNames[i]);
        }
    }

    std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device()()));
}

void MainWindow::firstCardSelected(QPushButton *button) {
    if (isCorrect != 1) {
        if (selectedIndex != -1) {
            MainWindow::findChild<QPushButton *>(QString("pushButton_" + QString::number(selectedIndex)))->setText("?");
        }
        if (secondSelectedIndex != -1) {
            MainWindow::findChild<QPushButton *>(QString("pushButton_" + QString::number(secondSelectedIndex)))->setText("?");
        }
    }

    isCorrect = -1;
    selectedIndex = -1;
    secondSelectedIndex = -1;

    int cardIndex = button->objectName().split("_")[1].QString::toInt();
    if(isPressed[cardIndex] == 1) {
        return;
    }
    selectedIndex = cardIndex;
    selectedCard = cards[cardIndex];
    button->setText(selectedCard.c_str());
}

void MainWindow::secondCardSelected(QPushButton *button) {
    secondSelectedIndex = button->objectName().split("_")[1].QString::toInt();
    if(isPressed[secondSelectedIndex] == 1) {
        return;
    }
    if (selectedIndex == secondSelectedIndex) return;
    std::string currentCard = cards[secondSelectedIndex];
    button->setText(currentCard.c_str());
    if (selectedCard == currentCard) {
        curScore++;
        if (curScore == 30) {
            MainWindow::findChild<QLabel *>(QString("label"))->setText("YOU WIN! Press New Game to Play Again");
            return;
        }
        ui->scoreValue->setText(QString::number(curScore));
        isPressed[selectedIndex] = 1;
        isPressed[secondSelectedIndex] = 1;
        selectedCard = "";
        isCorrect = 1;
    }

    remTries--;
    ui->triesValue->setText(QString::number(remTries));
    selectedCard = "";
}

void MainWindow::buttonPressed() {
    QPushButton *button = (QPushButton *)sender();
    if (selectedCard == "") {
        firstCardSelected(button);
    }
    else {
        secondCardSelected(button);
    }
}

