#pragma once

// NOLINTBEGIN
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
// NOLINTEND

class WelcomeDialog : public QMessageBox { // NOLINT(cppcoreguidelines-special-member-functions)
    Q_OBJECT

  public:
    explicit WelcomeDialog(QWidget *parent = nullptr);
    ~WelcomeDialog() override = default;

  private:
    QVBoxLayout *layout;
};