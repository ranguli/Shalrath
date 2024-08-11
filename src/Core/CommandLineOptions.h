#pragma once

#include <QStringList>

class CommandLineOptions {
  public:
    explicit CommandLineOptions(const QStringList &arguments);

    [[nodiscard]] auto isFirstRun() const -> bool;

  private:
    bool firstRunFlag = false;

    void parseArguments(const QStringList &arguments);
};
