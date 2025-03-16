
#include <main_includes.cpp>

int main()
{
    // create a socket that can listen for traffic on a port.
    WSADATA sock;
    int result = WSAStartup(MAKEWORD(2, 2), &sock); // chatgpt: I'm curious about what all kind of things the WSAStartup() can do, also I'm curious about the arguments it takes and this MAKEWORD() func and what and why we use it here
    if (result != NO_ERROR)
    {
        printf("Error with WSAStartup(): %d\n", WSAGetLastError());
        return 1;
    }

    // create a listener for a socket
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // chatgpt: here I am curious about the arguments, AF_INET, SOCK_STREAM, IPPROTO_TCP,  what exactly do those represent and what are other options available and what are the implications of these options, and why would we use one over the other?
    if (listener == INVALID_SOCKET)
    {
        printf("Socket Failed: %d\n", WSAGetLastError());
        return 1;
    }

    // connect a to a port on the machine??
    // chatgpt: these next 4 lines here are of interest, I think I kinda get it, but I want to know more, so the first line appears to create an object that will link a socket to a port, the 2nd line looks like it's assigning a 'signed family' to AF_INET which I'm assuming means something about some type of strategy for how sockets and ports can be connected, the 3rd line I'm assuming is setting the specific IP address and port combo that we are going to utilize will allow traffic from any network since its a INADDR_ANY, and the 4th line is pretty obvious, its assigning the actual port and possibly opening it? I am curious what some other options are for the sin_family and the sin_addr.s_addr and why we would use those options and when, also I am curious about this htons() func and what all it actually does and how else it could be used or what not, I assume you get what I'm after at this point.
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);

    // bind the socket listener to the port
    result = bind(listener, (sockaddr *)&addr, sizeof(addr)); // chatgpt: I'm pretty sure I get this, it's just binding the listener to the port and socket, there's not really additional options to set at this point is there?
    if (result == SOCKET_ERROR)
    {
        printf("Bind Failed: %d\n", WSAGetLastError());
        closesocket(listener);
        WSACleanup();
        return 1;
    }

    listen(listener, 10); // chatgpt: I think this here is where the actual server is being "turned on" if you will, I believe the 10 is how many unhandled requests we can allow to wait in line at one time? does that make sense? what is a standard setting for something like this?

    std::cout << "Listening on PORT: 8080! \n";

    while (true)
    {
        SOCKET client = accept(listener, nullptr, nullptr); // chatgpt: here I understand this to be a method of creating a socket to handle a request when it comes in, I'd like to understand this further as well as understanding additional options and such that can occur here along with what is typically seen in different situations.
        printf("GOT A CONNECTION!\n");

        // building a response here, header and body
        const std::string body =
            "<script>alert(\"HOLY FUCK WE SENT JAVASCRIPT TO THE BROWSER FROM C++\")</script>"
            "<div>We in that ass now!</div>\n";

        std::stringstream headers;
        headers << "HTTP/1.1 200 OK\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << body.length() << " \r\n" // curl cares about context length, chrome doesn't!
                << "Accept-Ranges: bytes\r\n"
                << "Connection: close\r\n"
                << "\r\n";

        std::string res = headers.str() + body;
        const char *http_res = res.c_str();
        // end of response building

        int sent = send(client, http_res, strlen(http_res), 0); // chatgpt: this I understand as how to send a message back to a client that we've created a connection with, I'd like to understand more about options that can occur here and within the send() function, also along with the send() function are there other functions similarly that involve communication with the client we're connected to?
        if (sent == SOCKET_ERROR)
        {
            printf("That shit ain't send bruv: %d\n", WSAGetLastError());
            printf("closing client socket cause:  %d\n", sent);
            closesocket(client);
        }
        else
        {
            printf("RESPONSE SUCCESSFUL: closing socket \n");
            closesocket(client);
        }
    }

    printf("closing listener socket \n");
    closesocket(listener);
    WSACleanup();
}