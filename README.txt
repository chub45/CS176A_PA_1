UDP Client: Creates socket, asks user for input, sends input to server, and keeps reading from server until either the
"Sorry, cannot compute!" message is recognized or if the buffer contains only 1 number.

UDP Server: Creates a socket, receives input from socket, computes from buffer based on input from socket, sends result
back to socket until only 1 digit is left, and close connection. Process continues indefinitely.

TCP Client: Creates a socket, asks user for input, sends input to server, and keeps reading from server until either the
"Sorry, cannot compute!" message is recognized or if the buffer contains only 1 number.

TCP Server: Creates a socket, begins to listen for connection requests, accepts connection and creates a new socket for
that connection, reads input from that socket, computes from buffer based on input from socket, sends results back to
that socket until only 1 digit is left, and closes connection with that socket. Process continues indefinitely.
