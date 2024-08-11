#pragma once

#include <QStringList>

class CommandLineOptions {
  public:
    explicit CommandLineOptions(const QStringList &arguments);

    bool isFirstRun() const;

  private:
    bool firstRunFlag = false;

    void parseArguments(const QStringList &arguments);
};
