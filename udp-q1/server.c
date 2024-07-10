//
//  udp-int-word-server.c
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

const char *num_to_word(int num) {
    switch (num) {
        case 1: return "one";
        case 2: return "two";
        case 3: return "three";
        case 4: return "four";
        case 5: return "five";
        case 6: return "six";
        case 7: return "seven";
        case 8: return "eight";
        case 9: return "nine";
        case 10: return "ten";
        default: return "";
    }
}

int main() {
    // Step 1 - socket()
    int server;
    struct sockaddr_in servAddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    server = socket(AF_INET, SOCK_DGRAM, 0);

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Step 2 - bind()
    bind(server, (struct sockaddr*)&servAddr, sizeof(servAddr)); 
    printf("Listening...\n\n");

    // Step 3 - recvfrom()
    int cliMsg[10];
    recvfrom(server, cliMsg, sizeof(cliMsg), 0, (struct sockaddr*)&clientAddr, &addrSize);
    printf("Msg from client:\n");
    for(int i=0;i<10;i++){
        printf("%d ",cliMsg[i]);
    }

    char servMsg[200] = "";
    for (int i = 0; i < 10; i++) {
        strcat(servMsg, num_to_word(cliMsg[i]));
        strcat(servMsg, " ");
    }

    // Step 4 - sendto()
    sendto(server, servMsg, strlen(servMsg), 0, (struct sockaddr*)&clientAddr, addrSize);

    // Step 5 - close()
    close(server);
    return 0;
}
