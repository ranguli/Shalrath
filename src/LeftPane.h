#ifndef LEFTPANE_H
#define LEFTPANE_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>

class LeftPane : public QWidget {
    Q_OBJECT

public:
    LeftPane(QWidget *parent = nullptr);

    QTableWidget *table;
    QLineEdit *searchLineEdit;

private:
    void setupUI();
};

#endif // LEFTPANE_H
