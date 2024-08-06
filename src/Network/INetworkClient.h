/**
 * @file INetworkClient.h
 * @brief Declares the INetworkClient interface for performing network operations.
 * 
 * This header file defines the INetworkClient interface, which outlines the contract for
 * performing network operations in the application. 

 * This interface serves as a means of separation between "back-end" networking code
 * and "front-end" UI code. This allows the  core networking functionality to be  
 * decoupled from the UI, such that it can be tested and run independently from the UI, or 
 * even be migrated to a different user-interface in the future should it be necessary.
 * 
 * The INetworkClient interface includes:
 * - A pure virtual function for downloading the map database from a given URL.
 * 
 * Usage:
 * - Implement the INetworkClient interface in classes that perform network operations.
 * - Use pointers orThe references to INetworkClient in other classes to perform network tasks.
 * 
 * @see AsyncNetworkTaskUI
 * @see QuaddictedClient
 */

#pragma once

#include <string>

class INetworkClient {
public:
    virtual ~INetworkClient() = default;
    virtual std::string downloadMapDatabase(const std::string &url) = 0;
};
