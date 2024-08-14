#pragma once

#include <QHBoxLayout>
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
    auto setupSearchLayout() -> QHBoxLayout *;
    auto setupTable() -> QTableWidget *;
    void populateTableWithData();
};