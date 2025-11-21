#include <iostream>
// #include<exception>
// #include<stdexcept>
#include <winsock2.h>
using namespace std;

int main()
{
    try
    {
        // ******************Initialize Winsock******************
        WSADATA wsaData;
        int iResult;

        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0)
        {
            cout << "WSAStartup failed: " << iResult;
            return 1;
        }
        /********************************************************/

        SOCKET main_socket = INVALID_SOCKET;
        main_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // (int domain, int type, int protocol) | AF_INET -> IPv4; SOCK_STREAM -> Connection oriented; IPPROTO_TCP -> TCP IP protocol

        if (main_socket == INVALID_SOCKET)
        {
            std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
            WSACleanup(); // Clean up before exiting
            return 1;
        }



        while (true)
        {
        };

        closesocket(main_socket);
        WSACleanup();
    }
    catch (const std::exception &e)
    {
        cout << "ERROR: " << WSAGetLastError() << std::endl;
        cout << "ERROR e: " << e.what() << std::endl;
    }

    return 0;
}