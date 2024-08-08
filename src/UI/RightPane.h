#pragma once

#include <QComboBox>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>

class RightPane : public QFrame {
    Q_OBJECT

  public:
    RightPane(QWidget *parent = nullptr);

    QLabel *imageLabel;
    QTextBrowser *textBrowser;
    QPushButton *installButton;
    QPushButton *uninstallButton;
    QPushButton *playButton;
    QComboBox *episodeSelectButton;

  private:
    void setupUI();
};
