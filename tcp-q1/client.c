//
//  tcp-sq-cube-client.c
//  nw_lab
//
//  Created by Anna Ann Mathew on 10/07/24.
//

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
    int client;
    struct sockaddr_in servAddr;
    socklen_t addrSize;
    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Step 2 - connect()
    connect(client, (struct sockaddr*)&servAddr, sizeof(servAddr));
    
    // Step 3 - send()
    int buffer[] = {1, 2, 3, 4, 5};
    int arrayLen = sizeof(buffer) / sizeof(buffer[0]);
    
    // Step 3.2 - send array length to server
    send(client, &arrayLen, sizeof(arrayLen), 0);
    printf("Array length sent to server\n");

    // Step 3.3 - send array to server
    send(client, buffer, sizeof(buffer), 0);
    printf("Array sent to server\n");
    
    // Step 4 - recv()
    int buffer1[arrayLen], buffer2[arrayLen];

    // Step 4.1 - recv perfect square array
    recv(client, buffer1, sizeof(buffer1), 0);
    printf("Square array received:\n");
    for (int i = 0; i < arrayLen; i++) {
        printf("%d ", buffer1[i]);
    }
    printf("\n");
    
    // Step 4.2 - recv perfect cube array
    recv(client, buffer2, sizeof(buffer2), 0);
    printf("Cube array received:\n");
    for (int i = 0; i < arrayLen; i++) {
        printf("%d ", buffer2[i]);
    }
    printf("\n");
    
    // Step 5 - close()
    close(client);
    return 0;
}
