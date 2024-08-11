// NOLINTBEGIN
#include <QApplication>
#include <QSettings>
// NOLINTEND

#include "MainWindow.h"
#include "WelcomeDialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Use QSettings to check if the welcome dialog has been shown
    QSettings settings("YourCompany", "YourAppName");
    bool hasSeenWelcomeDialog = settings.value("hasSeenWelcomeDialog", false).toBool();

    // Continue with the rest of your application
    MainWindow mainWindow;
    mainWindow.show();

    if (hasSeenWelcomeDialog) {
        WelcomeDialog welcomeDialog;
        if (welcomeDialog.exec() == QDialog::Accepted) {
            settings.setValue("hasSeenWelcomeDialog", true);
        }
    }

    return app.exec();
}