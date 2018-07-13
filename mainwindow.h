#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QException>
#include <QtGlobal>
#include "ecalc.h"

namespace Ui {
class MainWindow;
}
//static var for storing past result
static QString ans;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void ans_pressed();
    void iodg_pressed();
    void iopc_pressed();
    void operatr_pressed();
    void numeric_button_pressed();
    void delete_1_char_pressed();
    void ac_pressed();
    void unary_minus_pressed();
    void equal_pressed();
};

#endif // MAINWINDOW_H
