#include "StatusBar.h"

#include <QStyle>

StatusBar::StatusBar(QWidget* parent) : QStatusBar(parent) {
    statusLabel = new QLabel(this);
    addPermanentWidget(statusLabel);
}

StatusBar::~StatusBar() {
    // Proper cleanup if needed
}

void StatusBar::displayMessage(const QString& message) { statusLabel->setText(message); }

void StatusBar::displayMessageWithIcon(const QString& message, const QPixmap& icon) {
    statusLabel->setPixmap(icon);
    statusLabel->setText(message);
}
