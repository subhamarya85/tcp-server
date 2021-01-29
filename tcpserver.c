#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<netdb.h>
#include<netinet/in.h>

#include<sys/socket.h>
#include<sys/types.h>


#define MAX 80
#define PORT 8080
#define SA struct sockaddr


void func(int sockfd)
{

	char buff[MAX];
	int n;


	for(;;)
	{

		bzero(buff,MAX);

		read(sockfd,buff,sizeof(buff));


		printf("From client : %s\t To client : ",buff);

		bzero(buff,MAX);

		n=0;


		while((buff[n++]=getchar())!='\n')
			;

		write(sockfd,buff,sizeof(buff));

		if(strncmp("exit",buff,4)==0)
		{
			printf("Server exit .....\n");
			break;
		}


	}
}





int main()
{


	int sockfd,confd,len,test;

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
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(PORT);


	if(test=(bind(sockfd, (SA*)&servaddr,sizeof(servaddr)))!=0)
	{
		printf("socket bind failed...\n");
		exit(0);
	}
	else
	{
		printf("Socket binded sucessfully....\n");
	}


	if((listen(sockfd,5))!=0)
	{
		printf("Listen Fsiled....\n");
		exit(0);
	}
	else
	{
		printf("server listening...\n");
	}

	len=sizeof(cli);

	while(1)
	{
		confd=accept(sockfd,(SA*)&cli,&len);
		if(confd==-1)
		{
			printf("connection failed.....\n");
			exit(0);
		}
		else
		{
			printf("connection accepted.....\n");
			func(confd);
		
			
		}
	}
	testserver(sockfd,confd,test);
	close(sockfd);


}
void testserver(int sockfd,int confd,int test)
{

	struct sockaddr_in servaddr;



	if(sockfd!=-1)
	{
		if(test==0)
		{
			if(confd>=0)
			{
				printf("Server Test Pass.......\n");
			}
			else
			{
				printf("Server test fail....\n");
			}
		}
		else
		{
			printf("Server test fail...\n");
		}
		
        
	}
	else
	{
		printf("Server test fail...\n");
	}

}
