#include"data.h"
int mysocket()
{
	int  sockfd;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
		exit(1);
	}
	return sockfd;
}
	struct sockaddr_in server_addr; 
	struct hostent *host; 
void mybezero(struct sockaddr_in *server_addr,struct hostent *host)
{
	bzero(server_addr,sizeof(struct sockaddr_in)); // 
	server_addr->sin_family=AF_INET;
	server_addr->sin_port=htons(portnumber);
	server_addr->sin_addr = *((struct in_addr *)host->h_addr);//?
}
void myconnect(int sockfd,struct sockaddr_in *server_addr)
{
	if(connect(sockfd,(struct sockaddr *)(server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno)); 
		exit(1); 
	}	
}
void mywrite(int sockfd,vpChat temp)
{
	int num;
    if((num = write(sockfd,temp,sizeof(stChat))) == -1)
    {
        printf("send error!\n");
	}
}
