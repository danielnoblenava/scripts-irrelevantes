#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
	int server_fd, new_socket;
	struct sockaddr_in address;
	char buffer[BUFFER_SIZE] = {};
	int addrlen = sizeof(address);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	
	listen(server_fd, 3);
	printf("Server listening on port %d...\n", PORT);
	
	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	
	read(new_socket, buffer, BUFFER_SIZE);
	printf("Client said: %s\n", buffer);
	send(new_socket, buffer, strlen(buffer), 0);
	printf("Echo message sent.\n");

	close(new_socket);
	close(server_fd);
	return 0;
}
