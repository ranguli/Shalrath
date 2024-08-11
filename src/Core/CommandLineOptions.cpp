#include "CommandLineOptions.h"

CommandLineOptions::CommandLineOptions(const QStringList &arguments) {
    parseArguments(arguments);
}

void CommandLineOptions::parseArguments(const QStringList &arguments) {
    for (const auto &arg : arguments) {
        if (arg == "--first-run") {
            firstRunFlag = true;
        }
        // Add more options here as needed
    }
}

bool CommandLineOptions::isFirstRun() const {
    return firstRunFlag;
}