#include"data.h"
void process_chat(int sockfd,vpChat temp)//私聊发送
{
	printf("\033[4B");
	printf("\n");
	printf("\033[24C");
    printf("                    启动私聊功能           ");
	printf("\033[26C");
	scanf("%s",temp->toname);
	printf("\n");
	printf("\033[86C");
	scanf("%s",temp->msg);
   	mywrite(sockfd,temp);
	printf("\033[4A");
	printf("\n");
	printf("\033[24C");
	printf("                      发送成功             ");
	printf("\033[7A");
	printf("\n");
	printf("\033[36C");
	printf("                                          ");
	printf("\033[1A");
	printf("\n");
	printf("\033[36C");
	printf("msg");
}
void process_insert()
{
	printf("\033[5B");
	printf("\n");
	printf("\033[24C");
    printf("                                        ");
	printf("\033[26C");
	printf("                       ");
	printf("\n");
	printf("\n");
	printf("\033[86C");
	printf("                       ");
	printf("\033[9A");
	printf("\n");
	printf("\033[36C");
	printf("                               ");
	printf("\033[1A");
	printf("\n");
	printf("\033[36C");
	printf("msginsert");
}
void process_all(int sockfd,vpChat temp)//群聊发送
{
	printf("\033[4B");
	printf("\n");
	printf("\033[24C");
    printf("                    启动群聊功能           ");
	printf("\033[26C");
	my_strcpy(temp->toname,"大家");
	printf("大家\n");
	printf("\n");
	printf("\033[86C");
	scanf("%s",temp->msg);
   	mywrite(sockfd,temp);
	printf("\033[4A");
	printf("\n");
	printf("\033[24C");
   	mywrite(sockfd,temp);
	printf("                      发送成功             ");
	printf("\033[7A");
	printf("\n");
	printf("\033[36C");
	printf("                                          ");
	printf("\033[1A");
	printf("\n");
	printf("\033[36C");
	printf("msg");
}
void process_expression(int sockfd,vpChat temp)//发送表情
{
	printf("\t\t\t*************表情服务***************\n");
	printf("\t\t\t\t您向大家发了一个笑脸！\n");
	my_strcpy(temp->toname,"大家");
	my_strcpy(temp->msg,"笑脸");
   	mywrite(sockfd,temp);
	printf("\n\t\t\t***********服务结束***************\n");
}
void process_welcome(int sockfd,vpChat temp)//发送常用语
{
	printf("\t*************常用语***************\n");
	printf("\t\t\t\t您给大家发了一个常用语！\n");
	my_strcpy(temp->toname,"大家");
	my_strcpy(temp->msg,"欢迎各位的到来！\n");
   	mywrite(sockfd,temp);
	printf("\n\t\t\t\t***********常用语服务结束***************\n");
}
void process_passwd(int sockfd,vpChat temp)//修改密码
{
	char* passwd1;
	char* passwd2;
	getchar();
	printf("\t\t\t\t请输入修改密码：\n");
    passwd1 = (char *)get_passwd();
	printf("\n");
	printf("\t\t\t\t请再次输入修改密码：\n");
	passwd2 = (char *)get_passwd();
	printf("\n");
	if(my_strcmp(passwd1,passwd2) == 0 )
	{
		my_strcpy(temp->passwd,passwd1);
     	mywrite(sockfd,temp);
	}
	else
	{
		printf("您输入的密码未确定，请重发命令进行修改密码");
	}
}
void process_boot(int sockfd,vpChat temp)//踢人
{
	printf("\t\t\t\t请输入您想要踢出本聊天室的人的名字:\n");
    scanf("%s",temp->toname);
   	mywrite(sockfd,temp);
}
void process_step(int sockfd,vpChat temp)//禁言
{
	printf("\t\t\t\t请输入您想要禁他言的人的名字:\n");
    scanf("%s",temp->toname);
   	mywrite(sockfd,temp);
}
void process_ban(int sockfd,vpChat temp)//解禁
{
	printf("\t\t\t\t请输入您想要解他言的人的名字:\n");
    scanf("%s",temp->toname);
   	mywrite(sockfd,temp);
}
void process_set(int sockfd,vpChat temp)//注销
{
	printf("\t\t\t\t请输入您想要注销的用户名:\n");
    scanf("%s",temp->toname);
   	mywrite(sockfd,temp);
}
void process_see(int socket,vpChat temp)//查看在线用户
{
     mywrite(socket,temp);
}
void process_data(int socket,vpChat temp)
{
	mywrite(socket,temp);
}
void process_send(int socket,vpChat temp)
{
	FILE *fp;
	char filename[40];
	printf("\t\t\t*************文件发送***************\n");
	printf("\t\t\t\t请输入您要发送文件的对象：\n");
	scanf("%s",temp->toname);
	printf("\t\t\t\t请输入您要发送的文件名(文件名不得超过40字节且文件最好超过800字节，如超过仅取前面800字节发送)：\n");
	scanf("%s",filename);
	if((fp = fopen(filename,"r")) == NULL)
	{
		printf("您要发送的文件不存在\n");
	}
	else
	{
		my_strcpy(temp->filename,filename);
	    char ch;
		int i = 0;
		while((ch = getc(fp)) != EOF)
		{
			temp->msg[i++] = ch;
			if(i >= 799)
			{
				break;
			}
		}
        temp->msg[i] = '\0';
		mywrite(socket,temp);
		fclose(fp);
		printf("\t\t\t\t************发送成功**************\n");
	}
}
void process_change(int socket,vpChat temp)
{
	printf("\t\t\t请输入您想要的用户名(小于20字节的用户名)：");
	scanf("%s",temp->toname);
		mywrite(socket,temp);
}
