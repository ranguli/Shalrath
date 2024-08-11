#include "Shalrath.h"
#include "CommandLineOptions.h"
#include "MainWindow.h"
#include "WelcomeDialog.h"
#include <QSettings>

Shalrath::Shalrath(int &argc, char **argv) : QApplication(argc, argv) {
    handleCommandLineOptions();
    initialize();
}

void Shalrath::handleCommandLineOptions() {
    CommandLineOptions options(arguments());

    if (options.isFirstRun()) {
        QSettings settings("YourCompany", "YourAppName");
        settings.remove("hasSeenWelcomeDialog");
    }
}

void Shalrath::initialize() {
    QSettings settings("YourCompany", "YourAppName");
    bool hasSeenWelcomeDialog = settings.value("hasSeenWelcomeDialog", false).toBool();

    if (!hasSeenWelcomeDialog) {
        WelcomeDialog welcomeDialog;
        if (welcomeDialog.exec() == QDialog::Accepted) {
            settings.setValue("hasSeenWelcomeDialog", true);
        } else {
            // If the user cancels the welcome dialog, exit the application
            exit(0);
        }
    }

    // Initialize and show the main window
    MainWindow mainWindow;
    mainWindow.show();

    exec(); // Start the application event loop
}
