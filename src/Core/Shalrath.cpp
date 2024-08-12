#include "Shalrath.h"
#include "CommandLineOptions.h"
#include "MainWindow.h"
#include "WelcomeDialog.h"
#include <QSettings>
#include <QThread>

Shalrath::Shalrath(int &argc, char **argv) : QApplication(argc, argv) {
    handleCommandLineOptions();
    initialize();
}

Shalrath::~Shalrath() = default;

void Shalrath::handleCommandLineOptions() {
    const CommandLineOptions options(arguments());

    if (options.isFirstRun()) {
        QSettings settings("YourCompany", "YourAppName");
        settings.remove("hasSeenWelcomeDialog");
    }
}

void Shalrath::initialize() const {
    QSettings settings("YourCompany", "YourAppName");
    const bool hasSeenWelcomeDialog = settings.value("hasSeenWelcomeDialog", false).toBool();

    if (!hasSeenWelcomeDialog) {
        WelcomeDialog welcomeDialog;

        // Connect the dialog's signal to the initialization method
        connect(&welcomeDialog, &WelcomeDialog::startInitialization, this, &Shalrath::initializeMapDatabase);

        // Connect progress updates to the WelcomeDialog's progress bar
        connect(this, &Shalrath::updateProgress, &welcomeDialog, &WelcomeDialog::setProgressBarPercentage);

        // Start the event loop with the dialog visible
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

void Shalrath::initializeMapDatabase() {
    // Until we implement the actual intialization we'll just mock it out.
    for (int i = 0; i <= 100; ++i) {
        QThread::msleep(50);
        emit updateProgress(i);
        QCoreApplication::processEvents();
    }

    // After the progress bar is complete, close the dialog
    QMetaObject::invokeMethod(qApp->activeModalWidget(), "accept", Qt::QueuedConnection);
}