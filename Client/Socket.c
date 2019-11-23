//
// Created by randall.guzman on 23/11/2019.
//

#include "Socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>

//Define el puerto por el que va a escuchar
#define PORT 9090

const char *initClient(char jsonString[]) {
    printf(jsonString);
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024] = {0};

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    printf("Client Socket Created Sucessfully.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.43.189");

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Connected to Server.\n");

    //Envia mensaje al servidor
    send(clientSocket, jsonString, strlen(jsonString),0);

}


