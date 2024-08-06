#include "StatusBar.h"

StatusBar::StatusBar(QWidget* parent)
    : QStatusBar(parent), iconLabel(new QLabel(this)) {
    addPermanentWidget(iconLabel);
    iconLabel->hide();
}

void StatusBar::displayMessage(const QString& message, int timeout) {
    iconLabel->hide();
    showMessage(message, timeout);
}

void StatusBar::displayMessageWithIcon(const QString& message, const QPixmap& icon, int timeout) {
    iconLabel->setPixmap(icon);
    iconLabel->show();
    showMessage(message, timeout);
}
