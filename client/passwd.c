#include"data.h"
void cmd_reg(int sockfd,vpChat temp)
{
	insert_reg();
	char *passwd;
	char *passwd1;
	scanf("%s",temp->name);
	getchar();
	printf("\033[60C");
	passwd =(char *)get_passwd();
	printf("\n");
	printf("\033[60C");
	passwd1 = (char *)get_passwd();
	if(my_strcmp(passwd,passwd1) == 0)
	{
	   
	   printf("\n");
	   printf("\033[50C");
       printf("正在注册，请稍等！\n");
	   my_strcpy(temp->passwd,passwd);
       mywrite(sockfd,temp);
       memset(temp,0,sizeof(stChat));
       temp->revert = -1;
	   read(sockfd,temp,sizeof(stChat));
	   if(temp->revert == REGOK)
	   {
		     sleep(1);
		     printf("\033[2A");
	         printf("\n");
	         printf("\033[50C");
    	     printf("您已注册成功,欢迎您的使用！\n");
	         printf("\033[50C");
		     printf("请记住你的ID号：%d",temp->flag);
	         printf("\033[2B");
	         printf("\n");
	   }
	   else if(temp->revert == REGNO)
	   {
		     sleep(1);
		     printf("\033[2A");
	         printf("\n");
	         printf("\033[50C");
		     printf("已有账户注册过此用户名！");
	         printf("\033[3B");
	         printf("\n");
	   }
	   else
	   {
		     sleep(1);
		     printf("\033[2A");
	         printf("\n");
	         printf("\033[50C");
		     printf("服务器未向您发送确定信息！");
	         printf("\033[3B");
	         printf("\n");
	   }
	}
	else
	{
	   printf("\n");
	   printf("\033[50C");
       printf("您输入的密码不一致！");
	   printf("\033[2B");
	   printf("\n");
	}
}
void cmd_log(int sockfd,vpChat temp)
{
	insert_log();
	scanf("%s",temp->name);
	getchar();
	printf("\033[60C"); 
    char *passwd;
	passwd =(char *)get_passwd();
	printf("\n");
	my_strcpy(temp->passwd,passwd);
    mywrite(sockfd,temp);
    printf("\n");
	printf("\033[50C");
    printf("正在登录，请稍等！\n");
}
void cmd_id(int sockfd,vpChat temp)
{
	insert_id();
	char *passwd;
	scanf("%d",&temp->flag);
	getchar();
	printf("\033[60C");
    passwd = (char *)get_passwd();
	printf("\n");
	my_strcpy(temp->passwd,passwd);
    mywrite(sockfd,temp);
    printf("\n");
	printf("\033[50C");
    printf("正在登录，请稍等！\n");
}

