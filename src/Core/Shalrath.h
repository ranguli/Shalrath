#pragma once

#include <QApplication>
#include <QStringList>

class Shalrath : public QApplication {
    Q_OBJECT

  public:
    Shalrath(int &argc, char **argv);
    ~Shalrath() override = default; // Ensure the destructor is defined

    void initialize();

  private:
    void handleCommandLineOptions();
    void showWelcomeDialogIfNeeded();
};
