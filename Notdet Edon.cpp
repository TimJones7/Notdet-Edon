
#include <iostream>
#include <WinSock2.h>

int main()
{
    //create a socket that can listen for traffic on a port.
    WSADATA sock;
    int result = WSAStartup(MAKEWORD(2, 2), &sock);
    if (result != NO_ERROR) {
        printf("Error with WSAStartup(): %d\n", WSAGetLastError());
        return 1;
    }

    //create a listener for a socket
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == INVALID_SOCKET) {
        printf("Socket Failed: %d\n", WSAGetLastError());
        return 1;
    }

    //connect a to a port on the machine??
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);

    //bind the socket listener to the port
    result = bind(listener, (sockaddr*)&addr, sizeof(addr));
    if (result == SOCKET_ERROR) {
        printf("Bind Failed: %d\n", WSAGetLastError());
        closesocket(listener);
        WSACleanup();
        return 1;
    }

    listen(listener, 10);

    std::cout << "Listening on PORT: 8080! \n";

    while (true) {
        SOCKET client = accept(listener, nullptr, nullptr);
        printf("GOT A CONNECTION!\n");

        const char* http_res = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: \r\n" //curl cares about context length, chrome doesn't!
            "Accept-Ranges: bytes\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<script>alert(\"HOLY FUCK WE SENT JAVASCRIPT TO THE BROWSER FROM C++\")</script><div>We in that ass now!</div>\n";

        int sent = send(client, http_res, strlen(http_res), 0);
        if (sent == SOCKET_ERROR) {
            printf("That shit ain't send bruv: %d\n", WSAGetLastError());
            printf("closing client socket cause:  %d\n", sent);
            closesocket(client);
        }
        else {
            printf("RESPONSE SUCCESSFUL: closing socket \n");
            closesocket(client);
        }
    }

    printf("closing listener socket \n");
    closesocket(listener);
    WSACleanup();
}