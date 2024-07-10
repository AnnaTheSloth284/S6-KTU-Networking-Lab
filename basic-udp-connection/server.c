//
//  udp-basic-server.c
//  nw_lab
//
//  Created by Anna Ann Mathew on 10/07/24.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
    //Step 1 - socket()
    int server;
    struct sockaddr_in servAddr;
    socklen_t addrSize = sizeof(servAddr);
    server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    //Step 2 - bind()
    bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr));
    printf("Listening...\n\n");
    
    //Step 3 - recvfrom()
    char servMsg[2000], cliMsg[2000];
    recvfrom(server, cliMsg, sizeof(cliMsg),0,(struct sockaddr *)&servAddr, &addrSize);
    printf("Msg from client:%s\n", cliMsg);
    
    //Step 4 - sendto()
    strcpy(servMsg, cliMsg);
    sendto(server, servMsg, strlen(servMsg), 0, (struct sockaddr*)&servAddr, addrSize);
    
    //Step 5 - close()
    close(server);
}
