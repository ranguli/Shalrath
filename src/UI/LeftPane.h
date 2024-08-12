#pragma once

#include <QLineEdit>
#include <QTableWidget>
#include <QWidget>

class LeftPane : public QWidget {
    Q_OBJECT

  public:
    LeftPane(QWidget *parent = nullptr);

  private:
    void setupUI();

    QTableWidget *table;
    QLineEdit *searchLineEdit;
};