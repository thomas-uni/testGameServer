#include <iostream>
#include <thread>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#define PORT 9999
#define BUFFER_SIZE 1024

void udp_server() {
  int my_socket;
  struct sockaddr_in server_addr, client_addr;
  char buffer[BUFFER_SIZE];

  my_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (my_socket < 0)
  {
    std::cerr << "Socket creation falied";
    return;
  }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if(bind(my_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
      std::cerr << "bind failed";
      close(my_socket);
      return;
    }

    std::cout << "UDP server listening on port " << PORT << "... " << std::endl;

    while(true)
    {
      socklen_t length = sizeof(client_addr);
      int n = recvfrom(my_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &length);
      if (n < 0)
      {
        std::cerr << "Receive failed" << std::endl;
      }
      buffer[n] = '\0';
      std::cout << "Client: " << buffer << std::endl;

      sendto(my_socket, buffer, n, 0, (struct sockaddr *)&client_addr, length);
    }
  close(my_socket);
}


int main() {
    std::thread server_thread(udp_server);
    server_thread.join();
    return 0;
}
