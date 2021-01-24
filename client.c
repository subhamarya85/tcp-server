#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<netdb.h>

#include<sys/socket.h>



#define MAX 80
#define PORT 8080
#define SA struct sockaddr


void func(int sockfd)
{

	char buff[MAX];
	int n;


	for(;;)
	{

		bzero(buff,sizeof(buff));



		printf("Enter the string : ");

		n=0;


		while((buff[n++]=getchar())!='\n')
			;

		write(sockfd,buff,sizeof(buff));

		bzero(buff,sizeof(buff));

		read(sockfd,buff,sizeof(buff));

		printf("From server : %s",buff);

		if((strncmp(buff,"exit",4))==0)
		{
			printf("client exit .....\n");
			break;
		}


	}
}





int main()
{


	int sockfd,test;

	struct sockaddr_in servaddr,cli;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("Socket CReation Failed ..\n");
		exit(0);
	}
	else
	{
		printf("Socket Created Sucessfully.....\n");

	}


	bzero(&servaddr,sizeof(servaddr));


	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(PORT);


	if(test=(connect(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0)
	{
		printf("connection with server  failed...\n");
		exit(0);
	}
	else
	{
		printf("connected to the server  sucessfully....\n");
	}




	func(sockfd);


	testclient(sockfd,test);


	close(sockfd);

}

void testclient(int sockfd,int test)
{


	if(sockfd==0)
	{
		if(test==0)
		{
			printf("Client Test Pass....\n");
		}
		else
		{
			printf("Client Test Fail.....\n");
		}

	}
}
