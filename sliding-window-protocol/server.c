//
//  tcp-select-repeat-server.c
//  nw_lab
//
//  Created by Anna Ann Mathew on 11/07/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10

int main() {
    // Step 1 - socket()
    int server;
    struct sockaddr_in servAddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    server = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    
    // Step 2 - bind()
    bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr));
    
    // Step 3 - listen()
    if (listen(server, 5) == 0)
        printf("Listening\n");
    
    // Step 4 - accept()
    int newSock = accept(server, (struct sockaddr *)&clientAddr, &addrSize);
    
    //Step 5 and 6
    char bufferin[256];
    char bufferout[256];
    int framesReceived[TOTAL_FRAMES] = {0};
    int i = 0, ack, expectedFrame = 0;

    while (1) {
        memset(bufferin, 0, sizeof(bufferin));
        recv(newSock, bufferin, sizeof(bufferin), 0);
        sscanf(bufferin, "%d", &i);
        
        if (framesReceived[i] == 0) {
            framesReceived[i] = 1;
            printf("Frame %d received\n", i);
        }

        while (framesReceived[expectedFrame] == 1 && expectedFrame < TOTAL_FRAMES) {
            expectedFrame++;
        }

        if (expectedFrame == TOTAL_FRAMES) break;

        snprintf(bufferout, sizeof(bufferout), "ack%d", expectedFrame);
        send(newSock, bufferout, sizeof(bufferout), 0);
    }
    
    // Step 5 - close()
    close(newSock);
    close(server);
    return 0;
}
