#ifndef LEFTPANE_H
#define LEFTPANE_H

#include <QLineEdit>
#include <QTableWidget>
#include <QWidget>

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
