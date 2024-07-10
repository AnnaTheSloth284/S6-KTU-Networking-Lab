//
//  tcp-sq-cube-server.c
//  nw_lab
//
//  Created by Anna Ann Mathew on 10/07/24.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    // Step 1 - socket()
    int server;
    struct sockaddr_in servAddr;
    socklen_t addrSize;
    server = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Step 2 - bind()
    bind(server, (struct sockaddr*)&servAddr, sizeof(servAddr));
    
    // Step 3 - listen()
    if (listen(server, 5) == 0) {
        printf("Listening...\n");
    } else {
        printf("Failed...\n");
    }
    
    // Step 4 - accept()
    int newSock = accept(server, (struct sockaddr*)&servAddr, &addrSize);
    
    // Step 5 - recv()
    // Step 5.1 - recv array length
    int arrayLen;
    recv(newSock, &arrayLen, sizeof(arrayLen), 0);
    printf("Length of array received: %d\n", arrayLen);
    
    // Step 5.2 - recv array
    int buffer[arrayLen];
    recv(newSock, buffer, sizeof(buffer), 0);
    printf("Array received\n");
    
    // Step 6 - process and send()
    int arrsq[arrayLen];
    int arrcube[arrayLen];
    
    for (int i = 0; i < arrayLen; i++) {
        arrsq[i] = buffer[i] * buffer[i];
        arrcube[i] = buffer[i] * buffer[i] * buffer[i];
    }
    
    // Step 6.1 - send square array
    send(newSock, arrsq, sizeof(arrsq), 0);
    printf("Perfect square array sent to client\n");
    
    // Step 6.2 - send cube array
    send(newSock, arrcube, sizeof(arrcube), 0);
    printf("Perfect cube array sent to client\n");
    
    // Step 7 - close()
    close(newSock);
    close(server);
    return 0;
}
