//
//  tcp-select-repeat-client.c
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
    int client;
    struct sockaddr_in servAddr;
    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Step 2 - connect()
    connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));
    
    //Step 3 and 4
    char bufferin[256];
    char bufferout[256];
    int framesSent[TOTAL_FRAMES] = {0};
    int ack, base = 0, nextFrame = 0;

    while (1) {
        while (nextFrame < base + WINDOW_SIZE && nextFrame < TOTAL_FRAMES) {
            snprintf(bufferout, sizeof(bufferout), "%d", nextFrame);
            send(client, bufferout, sizeof(bufferout), 0);
            printf("Frame %d sent\n", nextFrame);
            framesSent[nextFrame] = 1;
            nextFrame++;
        }

        memset(bufferin, 0, sizeof(bufferin));
        recv(client, bufferin, sizeof(bufferin), 0);
        sscanf(bufferin, "ack%d", &ack);

        printf("Ack %d received\n", ack);

        if (ack >= base) {
            base = ack + 1;
        }

        if (base == TOTAL_FRAMES) break;
    }
    
    // Step 5 - close()
    close(client);
    return 0;
}
