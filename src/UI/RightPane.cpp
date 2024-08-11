#include "RightPane.h"

// NOLINTBEGIN
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
// NOLINTEND

RightPane::RightPane(QWidget *parent) : QFrame(parent) {
    setupUI();
}

const int THUMBNAIL_MAX_WIDTH = 300;
const int THUMBNAIL_MAX_HEIGHT = 200;

void RightPane::setupUI() {
    setFrameShape(QFrame::Box); // Example frame shape
    setFrameShadow(QFrame::Raised);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add an image placeholder at the top
    imageLabel = new QLabel(this);

    // Load and scale the image
    QPixmap pixmap(":/image.png");
    QPixmap scaledPixmap = pixmap.scaled(THUMBNAIL_MAX_WIDTH, THUMBNAIL_MAX_HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    // Add a text widget below the image
    textBrowser = new QTextBrowser(this);
    textBrowser->setText("This is a placeholder for a paragraph of text. It is "
                         "not editable by the user.");
    layout->addWidget(textBrowser);

    // Add a horizontal layout for the "Install" and "Uninstall" buttons
    auto *installationButtons = new QHBoxLayout(this);
    installButton = new QPushButton("Install", this);
    uninstallButton = new QPushButton("Uninstall", this);

    installationButtons->addWidget(installButton);
    installationButtons->addWidget(uninstallButton);

    layout->addLayout(installationButtons);

    // Add a horizontal layout for the "Play" button and episode selection
    auto *playButtons = new QHBoxLayout(this);
    playButton = new QPushButton("Play", this);
    episodeSelectButton = new QComboBox(this);

    playButtons->addWidget(playButton);
    playButtons->addWidget(episodeSelectButton);

    layout->addLayout(playButtons);
}
