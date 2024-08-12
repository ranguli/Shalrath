// NOLINTBEGIN
#include <QLabel>
#include <QSpacerItem>
#include <QStyle>
// NOLINTEND

#include "WelcomeDialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent)
    : QDialog(parent), mainLayout(new QVBoxLayout(this)), progressBar(new QProgressBar(this)) {
    setWindowTitle(tr("Welcome"));

    // NOLINTBEGIN(cppcoreguidelines-owning-memory)
    auto *iconLabel = new QLabel(this);
    iconLabel->setPixmap(style()->standardPixmap(QStyle::SP_MessageBoxInformation));

    // Center the text and add a newline after the first sentence
    auto *textLabel = new QLabel(tr("Welcome to Shalrath!\nWould you like to update the map database?"), this);
    textLabel->setAlignment(Qt::AlignCenter); // Center-align the text
    // NOLINTEND(cppcoreguidelines-owning-memory)

    auto *headerLayout = new QHBoxLayout(); // NOLINT(cppcoreguidelines-owning-memory)
    headerLayout->addWidget(iconLabel);
    headerLayout->addWidget(textLabel);
    mainLayout->addLayout(headerLayout);

    const int progressBarRange = 100;
    progressBar->setRange(0, progressBarRange);
    progressBar->setValue(0);
    mainLayout->addWidget(progressBar);

    // Add padding below the progress bar
    // NOLINTBEGIN(cppcoreguidelines-owning-memory)
    const int progressBarPadding = 20;
    auto *spacer = new QSpacerItem(0, progressBarPadding, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mainLayout->addItem(spacer);

    // Resize buttons without moving them
    const int buttonWidth = 75;
    const int buttonHeight = 30;
    const QSize buttonSize(buttonWidth, buttonHeight);

    // Set up the buttons
    auto *buttonLayout = new QHBoxLayout();

    okButton = setupOkButton(buttonSize);

    cancelButton = new QPushButton(tr("Cancel"), this);
    // NOLINTEND(cppcoreguidelines-owning-memory)

    cancelButton->setFixedSize(buttonSize);

    buttonLayout->addStretch(); // Ensure buttons stay at their positions
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch(); // Ensure buttons stay at their positions
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    // Set a minimum size to make the window taller
    const int minimumHeight = 220;
    setMinimumHeight(minimumHeight);

    // Connect the "Ok" button to the initialization signal

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void WelcomeDialog::setProgress(int value) {
    progressBar->setValue(value);
}

QPushButton *WelcomeDialog::setupOkButton(QSize buttonSize) {
    okButton = new QPushButton(tr("OK"), this);
    okButton->setFixedSize(buttonSize);

    connect(okButton, &QPushButton::clicked, this, &WelcomeDialog::startInitialization);
    return okButton;
}