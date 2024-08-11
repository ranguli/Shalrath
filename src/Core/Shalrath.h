#pragma once

#include <QApplication>
#include <QStringList>

class Shalrath : public QApplication { // NOLINT(cppcoreguidelines-special-member-functions)
    Q_OBJECT

  public:
    Shalrath(int &argc, char **argv);
    ~Shalrath() override = default; // Ensure the destructor is defined

    void initialize();

  private:
    void handleCommandLineOptions();
    void showWelcomeDialogIfNeeded();
};
