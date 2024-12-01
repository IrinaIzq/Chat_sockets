// This code is the client, who connects to the server and sends messages without UI
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024
#define PORT 8080

SOCKET client_socket;
int running = 1;

DWORD WINAPI receive_thread(LPVOID lpParam) {
    char buffer[BUFFER_SIZE];
    while (running) {
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            printf("Disconected from the server\n");
            running = 0;
            break;
        }
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
        fflush(stdout);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Use: %s <session_code> <nickname>\n", argv[0]);
        return 1;
    }

    WSADATA wsa;
    struct sockaddr_in server;
    char message[BUFFER_SIZE];
    
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Error initializing Winsock\n");
        return 1;
    }
    
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Error creating socket\n");
        return 1;
    }
    
    server.sin_addr.s_addr = inet_addr("Server_IP");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    
    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Conexion error\n");
        return 1;
    }
    
    printf("Conecting to the server\n");
    
    sprintf(message, "%s %s\n", argv[1], argv[2]);
    send(client_socket, message, strlen(message), 0);
    
    // Create thread to recieve menssages
    HANDLE hThread = CreateThread(NULL, 0, receive_thread, NULL, 0, NULL);
    
    // Main loop to send messages
    while (running) {
        if (fgets(message, BUFFER_SIZE, stdin) == NULL) break;
        
        if (strcmp(message, "quit\n") == 0) {
            running = 0;
            break;
        }
        
        if (send(client_socket, message, strlen(message), 0) < 0) {
            printf("Error sending menssage\n");
            break;
        }
    }
    
    closesocket(client_socket);
    WSACleanup();
    
    if (hThread != NULL) {
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);
    }
    
    return 0;
}