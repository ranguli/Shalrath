#pragma once

#include <QLabel>
#include <QPixmap>
#include <QStatusBar>

class StatusBar : public QStatusBar {
    Q_OBJECT

   public:
    explicit StatusBar(QWidget* parent = nullptr);
    ~StatusBar();

   public slots:
    void displayMessage(const QString& message);
    void displayMessageWithIcon(const QString& message, const QPixmap& icon);

   private:
    QLabel* statusLabel;
};
