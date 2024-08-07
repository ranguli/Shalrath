#pragma once

#include <QStatusBar>
#include <QString>
#include <QLabel>
#include <QPixmap>

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
