# Chat Application

This application is a simple chat server and client built using C and Winsock. It allows multiple clients to connect to a server and exchange messages in real-time. Each client must provide a session code and a nickname to join the chat.

## Features
- Multiple clients can connect to the server.
- Clients can send and receive messages.
- The server broadcasts messages to all connected clients.
- Each client is identified by a unique nickname.

## Requirements
- Windows operating system (due to the use of Winsock).
- GCC compiler (or any compatible C compiler).
- Ensure that the Winsock library is available.

## How to Compile and Run

### Server
1. Open a terminal and navigate to the directory containing `server.c`.
2. Compile the server code using the following command:
   ```bash
   gcc server.c -o server.exe -lws2_32
   ```
3. Run the server:
   ```bash
   .\server.exe
   ```

### Client
1. Open another terminal and navigate to the directory containing `client.c`.
2. Compile the client code using the following command:
   ```bash
   gcc client.c -o client.exe -lws2_32
   ```
3. Run the client with the session code and nickname as arguments:
   ```bash
   .\client.exe <session_code> <nickname>
   ```
   Replace `<session_code>` with the session code generated by the server and `<nickname>` with your desired nickname.

## Example
1. Start the server:
   ```bash
   .\server.exe
   ```
   The server will display the session code.
   
2. Start one or more clients:
   ```bash
   .\client.exe ABC123 MyNickname
   ```

3. Clients can now send messages to each other through the server.

## Notes
- Ensure that the server is running before starting any clients.
- The session code must match the one generated by the server for clients to connect successfully.
- To exit the client, type `quit` and press Enter.

## Troubleshooting
- If you encounter issues with `winsock2.h` not found, ensure that your development environment is set up correctly for Windows development.
- Make sure to link against the Winsock library (`-lws2_32`) during compilation.