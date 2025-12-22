#include "../../../include/zen/tcp/tcpServer.hpp"
#include "../../../include/zen/tcp/clientSession.hpp"
#include <sstream>

int main()
{
    TcpServer tcp(8080);

    while (true)
    {

        SOCKET client_socket = accept(tcp.getMainSocket(), NULL, NULL);
        if(client_socket == INVALID_SOCKET){
            std::cerr<< "Accept failed" << WSAGetLastError() << std::endl;
            continue;
        }

        {
            ClientSession cs(client_socket);

            std::stringstream ss;

            ss << cs.recvFromClient();

            std::cout << ss.rdbuf() << std::endl;

            std::string str =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "Content-Length: 187\r\n"
                "\r\n"
                "<!DOCTYPE html>\n"
                "<html lang=\"en\">\n"
                "<head>\n"
                "    <meta charset=\"UTF-8\">\n"
                "    <title>Socket Test</title>\n"
                "</head>\n"
                "<body>\n"
                "    <h1>Socket Test Successful</h1>\n"
                "    <p>If you see this, HTML was transmitted correctly.</p>\n"
                "</body>\n"
                "</html>\n";

            cs.sendToClient(str);
        }
    }
    return 0;
}