// TCP SERVER FLOW
// create() - To Create Socket
// bind() - To Bind Socket To Server Address
// listen() - Socket is in passive mode and listens for client to approach and make connection
// accept() - Connection between Server and Client is established
// Ready to transfer data
  
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
// Includes core socket functions like bind(), accept(), listen()
#include <sys/socket.h> 
#include <sys/types.h>
// Sending/Receiving Data on the socket read(), write(), close()
#include <unistd.h> 
// Functions ask the OS to resolve the name to an IP address
// The OS will ask a DNS server if needed
#include <netdb.h> 

#include <netinet/in.h>  

// 80 bytes of memory per message
#define MAX 80
#define PORT 8080

#define SA struct sockaddr

static void do_something(int connfd) {
    char rbuf[64] = {};
    ssize_t n = read(connfd, rbuf, sizeof(rbuf) - 1);
    if (n < 0) {
        msg("read() error");
        return;
    }
    printf("client says: %s\n", rbuf);

    char wbuf[] = "world";
    write(connfd, wbuf, strlen(wbuf));
}

int main(){
    int sockfd;

    // IPv4+TCP AF_INET SOCK_STREAM
    // IPv4+UDP AF_INET SOCK_DGRAM
    // IPv6+TCP AF_INET6 SOCK_STREAM
    // IPv6+UDP AF_INET6 SOCK_DGRAM
    sockfd = socket(AF_INET, SOCK_STREAM, 0);


    int val = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));


    // struct sockaddr_in {
    //     uint16_t       sin_family; // AF_INET
    //     uint16_t       sin_port;   // port in big-endian
    //     struct in_addr sin_addr;   // IPv4
    // };

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = htonl(0);

    int rv = bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr));

    if(rv) {exit(0);}

    rv = listen(sockfd, SOMAXCONN);
    if (rv) { exit(0); }

    while(true)
    {
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            continue;   // error
        }

        close(connfd);
    }
}

