#include "simconnectthread.ih"

#include <chrono>

bool SimconnectThread::tryConnecting()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    bool couldConnect = false;

    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()
                                                                 - begin)
             .count()
           < 5000)
    {
        if (SUCCEEDED(SimConnect_Open(&d_simConnectHandle, "PFD Companion Server", NULL, 0, 0, 0)))
        {
            couldConnect = true;
            quit = false;

            emit connected();

            break;
        }
    }

    if (!couldConnect)
    {
        emit receivedError("Could not connect to simconnect. Make sure the sim is running.");
        emit simConnectionFailed();
    }


    return couldConnect;
}
