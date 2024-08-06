/**
 * @file AsyncNetworkTaskUI.cpp
 * @brief Implements the AsyncNetworkTaskUI class for performing network tasks asynchronously.
 * 
 * This source file provides the implementation for the AsyncNetworkTaskUI class, which handles
 * the execution of network tasks in a separate thread to prevent blocking the UI. The class uses
 * Qt's signals and slots mechanism to facilitate communication between the worker thread and the
 * main UI thread.
 * 
 * The AsyncNetworkTaskUI constructor initializes the class with a pointer to an INetworkClient
 * object, which performs the actual network operations. The doWork() slot executes the network
 * task and emits signals upon completion to notify the main thread of the results.
 * 
 * Key functionalities implemented:
 * - Initializing the worker with an INetworkClient object.
 * - Executing network tasks in the doWork() slot.
 * - Emitting the resultReady() signal with the task results.
 * - Emitting the finished() signal upon task completion for thread cleanup.
 *
 */

#include "AsyncNetworkTaskUI.h"
#include <QThread>

AsyncNetworkTaskUI::AsyncNetworkTaskUI(INetworkClient* client_, QObject* parent)
    : QObject(parent), client(client_) {}

void AsyncNetworkTaskUI::doWork(const QString& url) {
    QString result = QString::fromStdString(client->downloadMapDatabase(url.toStdString()));
    emit resultReady(result);
    emit finished();
}
