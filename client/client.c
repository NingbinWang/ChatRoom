#include"data.h"
#include"package.h"
int main(int argc, char *argv[]) 
{ 
	int nbytes;
	int sockfd; 
	pthread_t id;
	struct sockaddr_in server_addr; 
	struct hostent *host; 
    stChat temp;
	if(argc != 2) 
	{ 
		fprintf(stderr,"Usage:%s hostname \a\n",argv[0]); 
		exit(1); 
	} 

	if((host = gethostbyname(argv[1]))==NULL) 
	{ 
		fprintf(stderr,"Gethostname error\n"); 
		exit(1); 
	} 
    sockfd = mysocket();
    mybezero(&server_addr,host);
    myconnect(sockfd,&server_addr);
		char cmd[100];
        insert_start();
		memset(&temp,0,sizeof(stChat));
		int end = 1;//用与判断是否注册成功！
		int root;//用于判断是否为root
        while(end)
		{
			root = 0;
			printf("\t\t\t\t\t请输入相应的命令(如忘记请输help)");
			scanf("%s",cmd);
            temp.cmd = analy_cmd(cmd);
			switch(temp.cmd)
			{
				case REG:
                      {
                         cmd_reg(sockfd,&temp);
						 break;
			          }
			    case LOG:
					  {
                            cmd_log(sockfd,&temp);	
							if(my_strcmp(temp.name,"root") == 0)
							{
								root++;
							}
                            memset(&temp,0,sizeof(stChat));
	                        read(sockfd,&temp,sizeof(stChat));
	                        if(temp.revert == PASSWDOK)
	                        {
								 root++;
		                         sleep(1);
		                         printf("\033[2A");
	                             printf("\n");
	                             printf("\033[50C");
    	                         printf("您已登录成功,欢迎您的使用！\n");
								 sleep(1);
								 end = 0;
	                        }
							else if(temp.revert == ONLINEIN)
							{
		                         sleep(1);
		                         printf("\033[2A");
	                             printf("\n");
	                             printf("\033[50C");
								 printf("该用户已经登陆！\n");
								 printf("\033[2B");
							}
                        	else if(temp.revert == PASSWDNO)
                        	{
		                         sleep(1);
		                         printf("\033[2A");
	                             printf("\n");
	                             printf("\033[45C");
	                          	 printf("您输入的密码有误或者用户不存在！\n");
								 printf("\033[2B");
                           	}
                           	else
	                        {
		                        sleep(1);
		                        printf("\033[2A");
	                            printf("\n");
	                            printf("\033[45C");
	                           	printf("\t\t\t\t\t服务器未向您发送确定信息！\n");
								 printf("\033[2B");
	                        }
                            break;
					  }
			    case LOGID:
					  {
                            cmd_id(sockfd,&temp);	
							if(temp.flag == 10000)
							{
								root++;
							}
                            memset(&temp,0,sizeof(stChat));
	                        read(sockfd,&temp,sizeof(stChat));
	                        if(temp.revert == PASSWDOK)
	                        {
								 root++;
		                         sleep(1);
		                         printf("\033[2A");
	                             printf("\n");
	                             printf("\033[50C");
    	                         printf("您已登录成功,欢迎您的使用！\n");
								 sleep(1);
								 end = 0;
	                        }
							else if(temp.revert == ONLINEIN)
							{
		                         sleep(1);
		                         printf("\033[2A");
	                             printf("\n");
	                             printf("\033[50C");
								 printf("该用户已经登陆！\n");
								 printf("\033[2B");
							}
                        	else if(temp.revert == PASSWDNO)
                        	{
		                         sleep(1);
		                         printf("\033[2A");
	                             printf("\n");
	                             printf("\033[45C");
	                          	printf("您输入的密码有误或者用户不存在！\n");
								 printf("\033[2B");
                           	}
                           	else
	                        {
		                         sleep(1);
		                         printf("\033[2A");
	                             printf("\n");
	                             printf("\033[45C");
	                           	 printf("服务器未向您发送确定信息！\n");
								 printf("\033[2B");
	                        }
                            break;
					  }
			    case USERHELP:
					  {
                        insert_start();
						break;
					  }
				case USEREXIT:
					  {
						  exit(1);
					  }
				default:
					  {
						  printf("您输入的命令有误！\n");
						  sleep(1);
					  }
			}
		}
		if(root == 2)
		{
           insert_root(temp.name);
		}
		else
		{
		   insert_help(temp.name);
		}
		pthread_create(&id,NULL,read_test,(void *)(&sockfd));
	    time_t tp;
        while(1)
		{
	        time(&tp);
	        char *timedata = ctime(&tp);
			scanf("%s",cmd);
			if(root == 2)
			{
				temp.cmd = process_root(cmd);
			}
			else
			{
                temp.cmd = process_user(cmd);
			}
			switch(temp.cmd)
			  {
				  case CHAT:
					     {
							 my_strcpy(temp.time,timedata);
                             process_chat(sockfd,&temp);
							 sleep(1);
							 process_insert();
							 break;
						 }
				  case ALL:
						 {
							 my_strcpy(temp.time,timedata);
                             process_all(sockfd,&temp);
							 sleep(1);
							 process_insert();
							 break;
						 }
				  case SMILE:
						 {
							 my_strcpy(temp.time,timedata);
                             process_expression(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				  case WELCOME:
						 {
							 my_strcpy(temp.time,timedata);
							 process_welcome(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				  case EXIT:
						 {
							 exit(1);
							 sleep(2);
							 break;
						 }
				  case HELP:
						 {
		                     if(root == 2)
		                     {
                                     insert_root(temp.name);
		                     }
		                     else
	                         {
		                             insert_help(temp.name);
		                     }
							 sleep(2);
							 break;
						 }
				  case PASSWD:
						 {
							 my_strcpy(temp.time,timedata);
							 process_passwd(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				  case BOOT:
						 {
							 my_strcpy(temp.time,timedata);
							 process_boot(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				  case STEP:
						 {
							 my_strcpy(temp.time,timedata);
							 process_step(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				  case BAN:
						 {
							 my_strcpy(temp.time,timedata);
                             process_ban(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				  case SET:
						 {
							 my_strcpy(temp.time,timedata);
							 process_set(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				  case SEE:
						 {
							 process_see(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				  case DATA:
						 {
							 my_strcpy(temp.time,timedata);
							 process_data(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				   case SEND:
						 {
							 my_strcpy(temp.time,timedata);
							 process_send(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				   case CHANGE:
						 {
							 process_change(sockfd,&temp);
							 sleep(2);
							 break;
						 }
				default:
						 {
							 printf("\033[4B");
							 printf("\n");
							 printf("\033[36C");
						     printf("您输入的命令有误！");
							 printf("\033[7A");
							 printf("\n");
							 printf("\033[36C");
							 printf("                  ");
							 printf("\033[1A");
							 printf("\n");
							 printf("\033[36C");
							 break;
						 }
			  }
		}


	close(sockfd);
	exit(0); 
} 

