#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<iostream>
using namespace std;
#define PORT 8080
int server(){
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello= "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello client2!";
	
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	send(new_socket,hello,strlen(hello),0);  
	string temp;
	while(temp!="bye"){
	        char buffer[1024] = {0};
		valread = read( new_socket , buffer, 1024);
		printf("%s\n",buffer );
		cout<<"Enter a message>> ";
		string str="C1: ";  
		cin>>temp; str+=temp;  
		char message[str.size()+1];
		strcpy(message,str.c_str());
		send(new_socket,message,strlen(message),0); 
	}	
}
int client(){
	int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket not created \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
	 if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)	
    	{
        	printf("\nConnection failed \n");
        	return -1;
    	}
        valread = read( sock , buffer, 1024);
	printf("%s\n",buffer );
	cout<<"Enter a message>> ";
	string str="C1: "; cin>>str; 
	char message[str.size()+1];
	strcpy(message,str.c_str());
	send(sock,message,strlen(message),0); 
	string temp;
	while(temp!="bye"){
	        char buffer[1024] = {0};
		valread = read( sock , buffer, 1024);
		printf("%s\n",buffer );
		cout<<"Enter a message>> ";
		string str="C2: "; string temp; 
		cin>>temp; str+=temp;  
		char message[str.size()+1];
		strcpy(message, str.c_str());
		send(sock,message,strlen(message),0);
		 
	}
}
int main(int argc, char const *argv[])
{
	cout<<"Enter 1 for server and 2 for client\n";
	int x; cin>>x;
	if(x==1){
		server();
	}
	else if(x==2){
		client();
	}else{
    cout<<"Invalid choice";
  }
	return 0;
}
