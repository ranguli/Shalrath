#include "AsyncNetworkTaskUI.h"
#include <QThread>

AsyncNetworkTaskUI::AsyncNetworkTaskUI(INetworkClient* client_, QObject* parent)
    : QObject(parent), client(client_) {}

void AsyncNetworkTaskUI::doWork(const QString& url) {
    QString result = QString::fromStdString(client->downloadMapDatabase(url.toStdString()));
    emit resultReady(result);
    emit finished();
}
