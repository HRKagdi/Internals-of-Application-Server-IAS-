#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<iostream>
#include<netdb.h>
#include<sys/socket.h>
using namespace std;
#define PORT 443
char ip[100];
int findIP(const char * host)
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
		
	if ( (he = gethostbyname( host ) ) == NULL) 
	{
		herror("gethostbyname");
		return 1;
	}

	addr_list = (struct in_addr **) he->h_addr_list;
	
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		strcpy(ip , inet_ntoa(*addr_list[i]) );
		return 0;
	}
	
	return 1;
}

int main(int argc, char const *argv[]){
    string url; 
    cout<<"Enter the url of the website to visit: ";
    cin>>url;
    
    char hostName[url.size()+1];
    strcpy(hostName, url.c_str());
    int temp=findIP(hostName);
    cout<<ip<<" ";
         
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
       
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
	 if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)	
    	{
        	printf("\nConnection failed \n");
        	return -1;
    	}
    	char* request="GET https://hrkagdi.github.io/html/index.html";
    	send(sock,request,strlen(request),0);
        valread = read( sock , buffer, 1024);
	printf("%s\n",buffer );
}
