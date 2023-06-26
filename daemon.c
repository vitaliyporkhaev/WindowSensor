#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sensor_driver.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define max 256
const int port = 8080;






int main() {
    int sct = socket(AF_INET, SOCK_STREAM, 0);
    if (sct < 0) {
        fprintf(stderr, "FAiled to create socket\n");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in address;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (bind(sct, (struct sockaddr*)&address, sizeof(address)) < 0) {
        fprintf(stderr, "Failed to bind socket to port %d\n", port);
        shutdown(sct, SHUT_RDWR);
        exit(EXIT_FAILURE);
    }

    while (5) {
        int client_sct; 
        struct sockaddr_in client_address;
        if (listen(sct, 1) < 0) {
            fprintf(stderr, "Failed to listen socket\n");
            shutdown(sct, SHUT_RDWR);
            exit(EXIT_FAILURE);
        }
        socklen_t clilen = sizeof(client_address);
        client_sct= accept(sct, (struct sockaddr*)&client_address, &clilen);
        if (client_sct < 0) {
            fprintf(stderr, "Failed to accept client connection\n");
            shutdown(sct, SHUT_RDWR);
            exit(EXIT_FAILURE);
        }
        char buffer[max]; 
        int symb_c;    
        while (5) {
            memset(buffer, 0, max);
            symb_c = read(client_sct, &buffer, max);  
            if (symb_c < 0) {
                fprintf(stderr, "Error...\n");
                close(client_sct);
                shutdown(sct, SHUT_RDWR);
                exit(EXIT_FAILURE);
            }
            if (!strcmp(buffer, "remove_daemon")) {
                close(client_sct);
                shutdown(sct, SHUT_RDWR);
                return 0;
            }

            else if (!strcmp(buffer, "poweron")) {
                memset(buffer, 0, max);
                if (status())
                    strcpy(buffer, "Your device is already working");
                else
                    strcpy(buffer, "Your device started");
                start();
            } 

            else if (!strcmp(buffer, "poweroff")) {
                memset(buffer, 0, max);
                if (!status())
                    strcpy(buffer, "Your device is already turned off");
                else
                    strcpy(buffer, "Your device stopped");
                stop();
            } 

            else if (!strcmp(buffer, "curr_state")) {
                memset(buffer, 0, max);
                if (status())
                    strcpy(buffer, "Your device turned on");
                else
                    strcpy(buffer, "Your device turned off");
            } 

            else if (!strcmp(buffer, "get_temperature")) {
                memset(buffer, 0, max);
                if(status())
                    sprintf(buffer, "%f", temperatureIS());
                else
                    strcpy(buffer, "Your device turned off");
            } 

            else if (!strcmp(buffer, "get_humidity")) {
                memset(buffer, 0, max);
                if(status())
                    sprintf(buffer, "%f", humidityIS());
                else
                    strcpy(buffer, "Your device turned off");
            } 
            symb_c = write(client_sct, buffer, strlen(buffer));
            if (symb_c < 0) {
                fprintf(stderr, "Error...\n");
                close(client_sct);
                shutdown(sct, SHUT_RDWR);
                exit(EXIT_FAILURE);
            }
        }
    }
    shutdown(sct, SHUT_RDWR);
    return 0;
}