#include "AsyncNetworkTaskUI.h"

AsyncNetworkTaskUI::AsyncNetworkTaskUI(INetworkClient *client_, QObject *parent)
    : QObject(parent), client(client_) {}

AsyncNetworkTaskUI::~AsyncNetworkTaskUI() {}

void AsyncNetworkTaskUI::doWork(const QString &url) {
    std::string result = client->downloadMapDatabase(url.toStdString());
    emit resultReady(QString::fromStdString(result));
    emit finished();
}
