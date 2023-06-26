#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#define max 256
#define port 8080






int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error...\n");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error...\n");
        exit(EXIT_FAILURE);
    } 
    else
        printf("Daemon connection succeeded!\n");
    printf("Here is what you can find out: - status    - poweron    - poweroff\n - remove_daemon   - get_temperature    - get_humidity\n\n");
    char buf[max];
    int symb_c;
    while (5) {    
        memset(buf, 0, max);
        printf("What do you want to know? ");
        scanf("%s", buf);
        symb_c = write(sockfd, buf, strlen(buf));
        
        if (symb_c < 0) {
            printf("Error...\n");
            exit(EXIT_FAILURE);
        }

        memset(buf, 0, max);
        symb_c = read(sockfd, buf, max);
        if (symb_c < 0) {
            printf("Error...\n");
            exit(EXIT_FAILURE);
        }
        printf("Answer: %s\n", buf);
    }
}