#include <iostream>        
#include <unistd.h>        // OS operations
#include <sys/socket.h>    // sockets
#include <netinet/in.h>    // address + port
#include <cstring>        
#include <arpa/inet.h>
using namespace std;


int main()
{
   int server_socket = socket(AF_INET,SOCK_STREAM,0);
   if (server_socket < 0) {
       std::cout << "Socket creation failed\n";
       return 0;
   }



   struct sockaddr_in server_socket_address;   // defining the server
   memset(&server_socket_address, 0, sizeof(server_socket_address));

   server_socket_address.sin_family= AF_INET;   //use ipv4 
   server_socket_address.sin_addr.s_addr=INADDR_ANY; // ip address       contianer and the ip inside.
   server_socket_address.sin_port=htons(8080);    //use port 8080

   if (::bind(server_socket,                      // binding the socket to the os
         (struct sockaddr*)&server_socket_address,
         sizeof(server_socket_address)) == -1)
{
    cout << "Bind failed\n";
}
  listen(server_socket,3);                    //listening  through the socket 
  if (listen(server_socket, 3) < 0) {
    cout << "Listen failed\n";
}
 int client_socket = accept(server_socket,NULL,NULL);         //accepting
   if (client_socket < 0) {
    cout << "Accept failed\n";
}

char request_buffer[1024]={0};                // storage of packets 
int number_of_bytes_received = read(client_socket,request_buffer,sizeof(request_buffer));
cout << request_buffer << endl;
if (number_of_bytes_received < 0) {
    cout << "Read failed\n";
}

const char* response =                        
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "\r\n"
    "<h1>Hello from my C++ server</h1>";

send(client_socket, response, strlen(response), 0);        // sending the client a response 

    return 0;
}