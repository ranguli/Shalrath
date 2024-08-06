/**
 * @file AsyncNetworkTaskUI.h
 * @brief Declares the AsyncNetworkTaskUI class for performing network tasks asynchronously.
 * 
 * AsyncNetworkTaskUI utilizes Qt's signals and slots mechanism in order to execute a background 
 * network task in a separate thread. This is done so as not to block or otherwise affect the 
 * responsivness of the application's UI.
 * 
 * The AsyncNetworkTaskUI class encapsulates an INetworkClient object, which performs the actual
 * network operations. It is responsible for emitting signals to notify the main thread of task 
 * completion and results, as well as management of the thread lifecycle.
 * 
 * Usage:
 * - Instantiate AsyncNetworkTaskUI with a pointer to an INetworkClient object.
 * - Connect the doWork() slot to a signal that triggers network tasks.
 * - Connect the resultReady() signal to a slot in the main thread to handle results.
 * - Ensure proper thread cleanup by connecting the finished() signal to appropriate slots.
 * 
 * @see INetworkClient
 */

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
