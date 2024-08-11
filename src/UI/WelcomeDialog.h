#pragma once

// NOLINTBEGIN
#include <QDialog>
#include <QVBoxLayout>
// NOLINTEND

class WelcomeDialog : public QDialog {
    Q_OBJECT

  public:
    explicit WelcomeDialog(QWidget *parent = nullptr);
    ~WelcomeDialog() override = default;

    // Delete copy operations to prevent copying
    WelcomeDialog(const WelcomeDialog &) = delete;
    auto operator=(const WelcomeDialog &) -> WelcomeDialog & = delete;

    // Default move operations for efficiency
    auto operator=(WelcomeDialog &&) noexcept -> WelcomeDialog & = default;
    WelcomeDialog(WelcomeDialog &&) noexcept = default;

  private:
    QVBoxLayout *layout;
};
