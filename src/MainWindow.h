#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LeftPane.h"
#include "RightPane.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    LeftPane *leftPane;
    RightPane *rightPane;
};

#endif // MAINWINDOW_H
