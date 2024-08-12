// NOLINTBEGIN
#include <QLabel>
#include <QSpacerItem>
#include <QStyle>
#include <qprogressbar.h>
// NOLINTEND

#include "WelcomeDialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) : QDialog(parent), mainLayout(setupMainLayout()) {
    setWindowProperties();
    setLayout(mainLayout);
}

void WelcomeDialog::setWindowProperties() {
    setWindowTitle(tr("Welcome"));
    // Set a minimum size to make the window taller
    const int minimumHeight = 220;
    setMinimumHeight(minimumHeight);
}

auto WelcomeDialog::setupMainLayout() -> QVBoxLayout * {
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    mainLayout = new QVBoxLayout(this);

    auto headerLayout = setupHeaderLayout();
    mainLayout->addLayout(headerLayout);

    progressBar = setupProgressBar();
    mainLayout->addWidget(progressBar);

    // Add padding below the progress bar
    const int progressBarPadding = 20;
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    auto *spacer = new QSpacerItem(0, progressBarPadding, QSizePolicy::Minimum, QSizePolicy::Fixed);
    mainLayout->addItem(spacer);

    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    auto buttonLayout = setupButtonLayout();

    mainLayout->addLayout(buttonLayout);

    return mainLayout;
}

auto WelcomeDialog::setupHeaderLayout() -> QHBoxLayout * {
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    auto *iconLabel = new QLabel(this);
    iconLabel->setPixmap(style()->standardPixmap(QStyle::SP_MessageBoxInformation));

    // Center the text and add a newline after the first sentence
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    auto *textLabel = new QLabel(tr("Welcome to Shalrath!\nWould you like to update the map database?"), this);
    textLabel->setAlignment(Qt::AlignCenter); // Center-align the text

    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    auto *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(iconLabel);
    headerLayout->addWidget(textLabel);

    return headerLayout;
}

auto WelcomeDialog::setupButtonLayout() -> QHBoxLayout * {
    const int buttonWidth = 75;
    const int buttonHeight = 30;
    const QSize buttonSize(buttonWidth, buttonHeight);

    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    auto *buttonLayout = new QHBoxLayout();

    okButton = setupOkButton(buttonSize);
    cancelButton = setupCancelButton(buttonSize);

    buttonLayout->addStretch(); // Ensure buttons stay at their positions
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch(); // Ensure buttons stay at their positions

    return buttonLayout;
}

auto WelcomeDialog::setupProgressBar() -> QProgressBar * {
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    progressBar = new QProgressBar(this);

    const int progressBarRange = 100;
    progressBar->setRange(0, progressBarRange);
    progressBar->setValue(0);

    return progressBar;
}

void WelcomeDialog::setProgressBarPercentage(int value) {
    progressBar->setValue(value);
}

auto WelcomeDialog::setupOkButton(QSize buttonSize) -> QPushButton * {
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    okButton = new QPushButton(tr("OK"), this);
    okButton->setFixedSize(buttonSize);

    connect(okButton, &QPushButton::clicked, this, &WelcomeDialog::startInitialization);
    return okButton;
}

auto WelcomeDialog::setupCancelButton(QSize buttonSize) -> QPushButton * {
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    cancelButton = new QPushButton(tr("Cancel"), this);
    cancelButton->setFixedSize(buttonSize);

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    return cancelButton;
}
