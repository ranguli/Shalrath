#include "RightPane.h"

#include <QHBoxLayout>
#include <QPixmap>
#include <QVBoxLayout>

RightPane::RightPane(QWidget *parent) : QFrame(parent) { setupUI(); }

void RightPane::setupUI() {
    setFrameShape(QFrame::Box);  // Example frame shape
    setFrameShadow(QFrame::Raised);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add an image placeholder at the top
    imageLabel = new QLabel;

    // Load and scale the image
    QPixmap pixmap(":/image.png");
    int maxWidth = 300;   // Example max width
    int maxHeight = 200;  // Example max height
    QPixmap scaledPixmap =
        pixmap.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    // Add a text widget below the image
    textBrowser = new QTextBrowser;
    textBrowser->setText(
        "This is a placeholder for a paragraph of text. It is "
        "not editable by the user.");
    layout->addWidget(textBrowser);

    // Add a horizontal layout for the "Install" and "Uninstall" buttons
    auto *installationButtons = new QHBoxLayout;
    installButton = new QPushButton("Install");
    uninstallButton = new QPushButton("Uninstall");

    installationButtons->addWidget(installButton);
    installationButtons->addWidget(uninstallButton);

    layout->addLayout(installationButtons);

    // Add a horizontal layout for the "Play" button and episode selection
    auto *playButtons = new QHBoxLayout;
    playButton = new QPushButton("Play");
    episodeSelectButton = new QComboBox();

    playButtons->addWidget(playButton);
    playButtons->addWidget(episodeSelectButton);

    layout->addLayout(playButtons);
}
