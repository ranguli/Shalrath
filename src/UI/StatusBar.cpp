// NOLINTBEGIN
#include <QLabel>
#include <QStatusBar>
// NOLINTEND

#include "StatusBar.h"

StatusBar::StatusBar(QWidget *parent) : QStatusBar(parent), messageLabel(new QLabel(this)), iconLabel(new QLabel(this)) {
    this->addWidget(iconLabel);
    this->addWidget(messageLabel, 1); // Ensure messageLabel expands to fill the space
}

void StatusBar::displayMessage(const QString &message) {
    messageLabel->setText(message);
}
