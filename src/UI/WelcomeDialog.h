#pragma once

#include <QDialog>

class WelcomeDialog : public QDialog {
    Q_OBJECT

  public:
    explicit WelcomeDialog(QWidget *parent = nullptr);
    ~WelcomeDialog();

  private:
    // UI components and methods for your welcome dialog
};
