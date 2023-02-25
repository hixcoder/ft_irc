# ft_irc



tcp et udp : des protocoles de transmission des données

tcp : transmission control protocol.
    . three-way handshake, guarntee that the data is received correctly.
udp : user datagram protocol
    . fire and forget protocol, faster than TCP, 

### Socket:
-  socket is an endpoint for sending and receiving data across a network.
-  The syntax : 
    ```c++
    int sockfd = socket(domain, type, protocol);
    ```
    . sockfd: socket descripto
    . domain: specifies communication domain (like address family).
    . type: communication type.
        * SOCK_STREAM: TCP
        * SOCK_DGRAM: UDP

### bind :
- the Socket need to bind with specific IP address amd port number, for linsting to incoming commections.
- The syntax : 
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    . sockfd : file descriptor returned by the socket.
    . addr : is a pointer to a sockaddr structure that 
        contains the IP address and port number to bind the socket to.
        struct sockaddr {
            unsigned short sa_family;    // Address family    // 2 bytes
            char sa_data[14];            // Up to 14 bytes of direct address
        };
        struct sockaddr_in {
            short int sin_family;           // Address family, AF_INET  // 2 bytes
            unsigned short int sin_port;    // Port number  // 2 bytes
            struct in_addr sin_addr;        // Internet address  // 4 bytes
            unsigned char sin_zero[8];      // Same size as struct sockaddr // 8 bytes
        };
        - The inet_addr() function is used to convert a string representation of an IPv4 address to 
            its binary form.
        - The htons() function is used to convert the port number to network byte order. 
    . addrlen : The size of addr in bytes.
### Listen : 
- listen: is a function that is used to put a server socket into a passive mode, waiting for incoming client connections.
- The syntax :
    int listen(int sockfd, int backlog);
    . sockfd : socket descriptor.
    . backlog :  the maximum length of the queue of pending connections that the kernel should allow for this socket.
### Accept :
- accept: is a function that is used in conjunction with sockets to accept incoming connection requests from clients and establish a new connection with the client.
- The syntax: 
    int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
    . sock: socket descriptor.
    . address: is a pointer to a sockaddr structe that will be filled with the address of the client that is making the connection request.
    . address_len: length of the sockaddr structure.
    . Accept return a new socket file descriptor that can be used to communicate with the client.


