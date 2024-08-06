#ifndef RIGHTPANE_H
#define RIGHTPANE_H

#include <QFrame>
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>
#include <QComboBox>

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

#endif // RIGHTPANE_H
