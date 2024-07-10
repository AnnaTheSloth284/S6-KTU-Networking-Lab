//
//  tcp-basic.c
//  nw_lab
//
//  Created by Anna Ann Mathew on 09/07/24.
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
    socklen_t addrSize;
    server = socket(AF_INET, SOCK_STREAM, 0);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    //Step 2 - bind()
    bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr));
    
    //Step 3 - listen()
    if(listen(server,5)==0)
        printf("Listening\n");
    else
        printf("Error\n");
    
    //Step 4 - accept()
    int newSock;
    newSock = accept(server, (struct sockaddr *)&servAddr,&addrSize);
    
    // Step 5 - recv()
    char buffer[1024];
    recv(newSock, buffer, sizeof(buffer), 0); //recv()
    printf("2. Data rcvd: %s", buffer);
    
    // Step 6 - send()
    strcpy(buffer,"Hi this is the server...\n");
    printf("3. Sending data to client...\n");
    send(newSock, buffer, sizeof(buffer), 0);
    
    // Step 7 - close()
    close(newSock);
    close(server);
}
