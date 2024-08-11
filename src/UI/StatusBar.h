#pragma once

// NOLINTBEGIN
#include <QLabel>
#include <QStatusBar>
// NOLINTEND

class StatusBar : public QStatusBar {
    Q_OBJECT

  public:
    explicit StatusBar(QWidget *parent = nullptr);

  public slots:
    void displayMessage(const QString &message);

  private:
    QLabel *messageLabel;
    QLabel *iconLabel;
};
