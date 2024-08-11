#include "WelcomeDialog.h"

// NOLINTBEGIN
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
// NOLINTEND

WelcomeDialog::WelcomeDialog(QWidget *parent) : QDialog(parent), layout(new QVBoxLayout(this)) {
    // layout is explicitly initialized in the initializer list
    QLabel *welcomeMessage = new QLabel(tr("Welcome to the Application!"), this);
    layout->addWidget(welcomeMessage);

    QPushButton *okButton = new QPushButton(tr("OK"), this);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
}
