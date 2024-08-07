/**
 * @file AsyncNetworkTaskUI.cpp
 * @brief Implements the AsyncNetworkTaskUI class for performing network tasks asynchronously.
 *
 * This class uses Qt's signals and slots mechanism to facilitate communication between the worker
 * thread and the main UI thread.
 *
 * The AsyncNetworkTaskUI constructor initializes the class with a pointer to an INetworkClient
 * object, which performs the actual network operations. The doWork() slot executes the network
 * task and emits signals upon completion to notify the main thread of the results.
 *
 * This class encapsulates an INetworkClient object, which performs the actual
 * network operations. It is responsible for emitting signals to notify the main thread of task
 * completion and results, as well as management of the thread lifecycle.
 *
 * Key functionalities implemented:
 * - Initializing the worker with an INetworkClient object.
 * - Executing network tasks in the doWork() slot.
 * - Emitting the resultReady() signal with the task results.
 * - Emitting the finished() signal upon task completion for thread cleanup.
 *
 * Usage:
 * - Instantiate AsyncNetworkTaskUI with a pointer to an INetworkClient object.
 * - Connect the doWork() slot to a signal that triggers network tasks.
 * - Connect the resultReady() signal to a slot in the main thread to handle results.
 * - Ensure proper thread cleanup by connecting the finished() signal to appropriate slots.
 *
 */

#include "AsyncNetworkTaskUI.h"

#include <QThread>

AsyncNetworkTaskUI::AsyncNetworkTaskUI(INetworkClient* client_, QObject* parent)
    : QObject(parent), client(client_) {}

void AsyncNetworkTaskUI::doWork(const QString& url) {
    emit taskStarted();
    QString result = QString::fromStdString(client->downloadMapDatabase(url.toStdString()));
    emit resultReady("Map updated");
    emit finished();
}
