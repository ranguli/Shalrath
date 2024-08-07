#pragma once

#include <QLabel>
#include <QPixmap>
#include <QStatusBar>
#include <QString>

class StatusBar : public QStatusBar {
    Q_OBJECT

   public:
    explicit StatusBar(QWidget* parent = nullptr);

   public slots:
    void displayMessage(const QString& message, int timeout = 0);
    void displayMessageWithIcon(const QString& message, const QPixmap& icon, int timeout = 0);

   private:
    QLabel* iconLabel;
};
