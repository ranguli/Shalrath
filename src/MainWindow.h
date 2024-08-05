#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    QTableWidget *table;
    QLabel *imageLabel;
    QTextBrowser *textBrowser;
    QLineEdit *searchLineEdit;
    QPushButton *installButton;
    QPushButton *uninstallButton;
};

#endif // MAINWINDOW_H
