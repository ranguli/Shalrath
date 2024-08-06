#pragma once

#include <QObject>
#include <QString>
#include "INetworkClient.h"

class AsyncNetworkTaskUI : public QObject {
    Q_OBJECT

public:
    explicit AsyncNetworkTaskUI(INetworkClient* client, QObject* parent = nullptr);

public slots:
    void doWork(const QString& url);

signals:
    void resultReady(const QString& result);
    void finished();

private:
    INetworkClient* client;
};
