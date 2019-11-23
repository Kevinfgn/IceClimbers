
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "Socket.h"
#include "ICE-Json.h"

//Define the port where the server is listening

int main() {
    char playerJson = jsonWriterPlayer(45,445,1,3);
    initClient(playerJson);
}