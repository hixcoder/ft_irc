# ft_irc



tcp et udp : des protocoles de transmission des données

tcp : transmission control protocol.
    . three-way handshake, guarntee that the data is received correctly.
udp : user datagram protocol
    . fire and forget protocol, faster than TCP, 

### Socket:
-  socket is an endpoint for sending and receiving data across a network.
-  syntax: 
    ```c++
    int sockfd = socket(domain, type, protocol);
    ```
    - sockfd: the socket file descriptor
    - domain: specifies communication domain (like address family).
    - type: communication type.
        - SOCK_STREAM: TCP
        - SOCK_DGRAM: UDP
### Setsockopt:
- setsockopt is a function that allows you to set options on a socket.
- syntax:
    ```c++
    int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
    ```
    - sockfd: the socket file descriptor
    - level: the protocol level at which the option resides

### bind :
- the Socket need to bind with specific IP address amd port number, for linsting to incoming commections.
- syntax :
    ```c++
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    ```
    - sockfd : file descriptor returned by the socket.
    - addr : is a pointer to a sockaddr structure that 
        contains the IP address and port number to bind the socket to.
        ```c++
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
        ```
        - The inet_addr() function is used to convert a string representation of an IPv4 address to 
            its binary form.
        - The htons() function is used to convert the port number to network byte order. 
    - addrlen : The size of addr in bytes.
### Listen : 
- listen: is a function that is used to put a server socket into a passive mode, waiting for incoming client connections.
- syntax :
    ```c++
    int listen(int sockfd, int backlog);
    ```
    - sockfd : socket descriptor.
    - backlog :  the maximum length of the queue of pending connections that the kernel should allow for this socket.
### Accept :
- accept: is a function that is used in conjunction with sockets to accept incoming connection requests from clients and establish a new connection with the client.
- syntax: 
    ```c++
    int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
    ```
    - sock: socket descriptor.
    - address: is a pointer to a sockaddr structe that will be filled with the address of the client that is making the connection request.
    - address_len: length of the sockaddr structure.
    - Accept return a new socket file descriptor that can be used to communicate with the client.
### Recv :
- recv :  used to receive data from a socket, it like ~read.
- syntax :
    ```c++
    int recv(int sockfd, void *buf, size_t len, int flags);
    ```
    - sockfd: the file descriptor of the socket to read from.
    - buf: a pointer to a buffer to store the received data.
    - len: the maximum length of the buffer // sizeof(buf).
    - flags: additional flags that modify the behavior of the function. MSG_WAITALL, MSG_DONTWAIT and MSG_PEEK.
### Send:
- send: is a system call used to send data over a socket.
- syntax:
    ```c++
    ssize_t send(int sockfd, const void *buf, size_t len, int flags);
    ```
    - flags: additional flags that modify the behavior of the function. MSG_CONFIRM, MSG_DONTROUTE and MSG_MORE.
### Poll:
- poll is a technique used to manage a collection of socket connections.
- it's used for checking if there is any I/O operation can be performed on a set of file descriptors without blocking.
- syntax:
    ```c++
    int poll(struct pollfd *fds, nfds_t nfds, int timeout);
    ```
    - fds: a pointer to an array of struct pollfd elements.
    ```c++
    struct pollfd {
	    int     fd;
	    short   events;
	    short   revents;
    };
    ```
        - fd: socket descriptor.
        - events:  events you want to monitor for file descriptor.
            - POLLIN: Data is available to be read from the file descriptor.
            - POLLOUT: Data can be written to the file descriptor without blocking.
            - POLLERR, POLLHUP(disconnected) and POLLNVAL(not open).
        - revents :  indicate which events actually occurred on the corresponding file descriptor, returned by poll.
    - nfds: the number of struct pollfd elements in the fds array.
    - timeout: specifies the time-out interval in milliseconds.
        - -1: if one file descriptor that is ready for I/O.
        - 0 : should return immediately. (poll without blocking)
        - positive integer : the number of milliseconds.


