#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <string>
#include <iostream>
#define MAX 80

using namespace std;


// TCP SERVER FLOW
// create() - To Create Socket
// Connect client socket to server

// Watch video on TCP servers in c++
// Continue writing client side from website

int main()
{

    int socketfd;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = htonl(0);

    int connfd = connect(socketfd, (const struct sockaddr *)&addr, sizeof(addr));
    if(connfd < 0) exit(0);

    // MSG_EOR for normal messages
    // MSG_OOB priority messages, passes message queues
    const char* message = "Hello Server";

    send(socketfd, message, MAX, MSG_EOR);

    char rbuf[64] = {};
    recv(socketfd, rbuf, MAX, MSG_PEEK);


    cout << "server says: " << rbuf << "\n";

    close(socketfd);

    return 0;

}