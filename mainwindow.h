#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void firstCardSelected(QPushButton *button);
    void secondCardSelected(QPushButton *button);

private slots:
    void buttonPressed();
    void newGamePressed();
};
#endif // MAINWINDOW_H
