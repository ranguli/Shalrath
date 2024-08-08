#pragma once

#include <QLabel>
#include <QPixmap>
#include <QStatusBar>

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
