#ifndef __COMMUNICATION_HPP__
#define __COMMUNICATION_HPP__
#include <Arduino.h>
#include <WiFi.h>

class Communication {
public:
    /**
     * @brief Possible results from many functions
     */
    enum Result {
        Success,
        CannotFindServer,
        NoWifi,
        NoData,
        DataExceededLength
    };
private:
    const char* ssid;
    const char* password;
    const char* serverIp;
    unsigned long serverPort;
    bool wifiConnected;
    const unsigned long maxConnectAttempts = 20;
    WiFiClient client;
    Result connectToServer();
    Result connectToWifi();
public:
    /**
     * @brief Construct a new Communication object
     * 
     * We may need to eventually move the server ip outside of the ctor
     * if we want to do some sort of ip scanning
     *
     * @param ssid 
     * @param password
     * @param serverIp 
     */
    Communication(const char* ssid, const char* password, const char* serverIp, unsigned long serverPort);

    /**
     * @brief Connect to the wifi, and server
     *
     * @return Result What happened
     */
    Result connect();

    /**
     * @brief Disconnect from server
     *
     * @return Result 
     */
    Result disconnect();

    /**
     * @brief Send some data
     * 
     * @return Result 
     */
    Result send(const char* buf);

    /**
     * @brief Receive some data
     *
     * @param buf 
     * @param size 
     * @return Result 
     */
    Result receive(char* buf, unsigned long size);

    /**
     * @brief Checks to see if we are connected to wifi, and the server
     *
     * @return Result 
     */
    Result isConnected();
};

#endif
