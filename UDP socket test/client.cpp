// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8080 
#define MAXLINE 1024 
  
#include <iostream>
#include "nlohmann/json.hpp"

using namespace nlohmann;

// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from client"; 
    struct sockaddr_in     servaddr; 
    struct sockaddr_in remaddr;

  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n, len; 
      
    len = sizeof(servaddr);
    socklen_t addrlen = sizeof(servaddr);

    for (int i = 0; i < 100; ++i)
    {  
        int tx=111, ty=222, tz=333;

        json j ={{"time",123},{"tvec",{{"tx",tx},{"ty",ty},{"tz",tz}}}}; //,"tvec",{{"tx",tx},{"ty",ty},{"tz",tz}},"quat",{{"qx",qx},{"qy",qy},{"qz",qz},{"qw",qw}},

        std::string serialized_string = j.dump();
        std::cout << serialized_string << std::endl;

        char *char_arr;
        char_arr = &serialized_string[0];


        sendto(sockfd, (const char *)char_arr, strlen(char_arr), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, len); 
        printf("Hello message sent.\n"); 
    }
  
    close(sockfd); 
    return 0; 
} 