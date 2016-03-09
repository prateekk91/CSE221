#include<iostream>
using namespace std;
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>
 
int main(int argc , char *argv[])
{
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;
	char *message;
	char buffer[256];
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		cout<<"Could not create socket"<<endl;
	}
		 
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 7000 );
		 
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		cout<<"bind failed"<<endl;
	}
	cout<<"bind done"<<endl;
	
	listen(socket_desc , 3);
	
	//Accept and incoming connection
    cout<<"Waiting for incoming connections..."<<endl;
    c = sizeof(struct sockaddr_in);
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
    	close (new_socket);
    }
     
    if (new_socket<0)
    {
        cout<<"accept failed"<<endl;
        return 1;
    }
     
    return 0;
}
