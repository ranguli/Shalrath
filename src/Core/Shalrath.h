#pragma once

#include <QApplication>
#include <QStringList>

class Shalrath : public QApplication { // NOLINT(cppcoreguidelines-special-member-functions)
    Q_OBJECT

  public:
    Shalrath(int &argc, char **argv);
    ~Shalrath() override;

    void initialize() const;

  signals:
    void updateProgress(int value);

  private:
    static void handleCommandLineOptions();
    void showWelcomeDialogIfNeeded();
    void initializeMapDatabase();
};
