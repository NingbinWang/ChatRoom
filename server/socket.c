#include"data.h"
void mybzero(struct sockaddr_in *sin)//对server_addr_in  结构进行赋值
{
	bzero(sin,sizeof(struct sockaddr_in));   /* 先清零 */
	sin->sin_family=AF_INET;                 //
	sin->sin_addr.s_addr=htonl(INADDR_ANY);  //表示接受任何ip地址   将ip地址转换成网络字节序
	sin->sin_port=htons(portnumber);         //将端口号转换成网络字节序
}
int mysocket()//调用socket函数创建一个TCP协议套接口
{
	int lfd;
	if((lfd = socket(AF_INET,SOCK_STREAM,0)) == -1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
		exit(1);
	}
	return lfd;
}
void mybind(int lfd,struct sockaddr_in *sin)	// 调用bind函数 将serer_addr结构绑定到sockfd上 
{
	if(bind(lfd,(struct sockaddr *)(sin),sizeof(struct sockaddr))==-1)
	{
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
		exit(1);
	}
}
void mylisten(int lfd)// 开始监听端口   等待客户的请求
{
	if(listen(lfd,20)==-1)
	{
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
		exit(1);
	}
}
int myaccept(int lfd,struct sockaddr_in *cin,socklen_t * addr_len)// 接受客户端的请求 
{
	int cfd;
	if((cfd=accept(lfd,(struct sockaddr *)cin,addr_len))==-1)
	{
		fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
		exit(1);
	}
	return cfd;
}
void mywrite(vpChat temp)
{
	int num;
    if((num = write(temp->sockfd,temp,sizeof(stChat))) == -1)
    {
        printf("send error!\n");
    }
}
