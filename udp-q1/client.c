//
//  udp-int-word-client.c
//  nw_lab
//
//  Created by Anna Ann Mathew on 10/07/24.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Step 1 - socket()
    int client;
    struct sockaddr_in servAddr;
    socklen_t addrSize = sizeof(servAddr);
    client = socket(AF_INET, SOCK_DGRAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Step 2 - sendto()
    int cliMsg[10];
    printf("Enter array of elements between 1 to 10 to server: ");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &cliMsg[i]);
    }
    sendto(client, cliMsg, sizeof(cliMsg), 0, (struct sockaddr*)&servAddr, addrSize);

    // Step 3 - recvfrom()
    char servMsg[200];
    recvfrom(client, servMsg, sizeof(servMsg), 0, (struct sockaddr*)&servAddr, &addrSize);
    printf("Received message:\n%s\n", servMsg);

    // Step 4 - close()
    close(client);
    return 0;
}
