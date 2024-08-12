#pragma once

// NOLINTBEGIN
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QSize>
#include <QVBoxLayout>
// NOLINTEND

class WelcomeDialog : public QDialog { // NOLINT(cppcoreguidelines-special-member-functions)
    Q_OBJECT

  public:
    explicit WelcomeDialog(QWidget *parent = nullptr);
    ~WelcomeDialog() override = default;

    void setProgress(int value); // Method to update the progress bar

  signals:
    void startInitialization(); // Signal to start initialization

  private:
    QVBoxLayout *mainLayout;
    QProgressBar *progressBar;
    QPushButton *okButton;
    QPushButton *cancelButton;

    QPushButton *setupOkButton(QSize buttonSize);
};
