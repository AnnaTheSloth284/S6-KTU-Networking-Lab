//
//  tcp-basic-client.c
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
    // Step 1 - socket()
    int client;
    struct sockaddr_in servAddr;
    socklen_t addrSize;
    client = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    //Step 2 - connect()
    connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));
    
    //Step 3 - send()
    char buffer[1024];
    printf("1. Sending data to server\n");
    strcpy(buffer,"Hi this is the client\n");
    send(client, buffer, sizeof(buffer), 0);
    
    //Step 4 - recv()
    recv(client, buffer, sizeof(buffer), 0);
    printf("4. Data rcvd: %s", buffer);
    
    //Step 5 - close()
    close(client);
}
