#include"data.h"
void *read_test(void* arg)
{
	int fd = *((int *)arg);
	int n;
	stChat temp;
	while(1)
	{
       n = read(fd,&temp,sizeof(stChat));
	   switch(temp.cmd)
	   {
		   case CHAT:
			   {
				   if(temp.revert == MYFLAGNO)
				   {
	                   printf("\033[5B");
	                   printf("\n");
	                   printf("\033[24C");

					   printf("您被禁言了，请联系管理员");
					   printf("\033[7A");
					   printf("\n");
					   printf("\033[36C");
				   }
				   else if(temp.revert == ONLINEOUT)
				   {
	                   printf("\033[5B");
	                   printf("\n");
	                   printf("\033[24C");
					   printf("您要对话的用户已经不在本聊天室了!");
					   printf("\033[7A");
					   printf("\n");
					   printf("\033[36C");
				   }
				   else if(temp.revert == CHATOK)
				   {
					   printf("\033[11B");
				       printf("\t%s\n",temp.time);
					   printf("\t %s    \t%s\n",temp.name,temp.msg);
					   printf("\n");
					   printf("\033[15A");
					   printf("\033[36C");

				   }
				   else
				   {
	                   printf("\033[5B");
	                   printf("\n");
	                   printf("\033[24C");
					   printf("服务器未向你发送正确信息");
					   printf("\033[7A");
					   printf("\n");
					   printf("\033[36C");
				   }

				   break;
			   }
		   case ALL:
			   {
				   if(temp.revert == MYFLAGNO)
				   {
	                   printf("\033[5B");
	                   printf("\n");
	                   printf("\033[24C");
					   printf("\n\t\t\t您被禁言了，请联系管理员\n");
					   printf("\033[7A");
					   printf("\n");
					   printf("\033[36C");
				   }
				   else
				   {
					   printf("\033[11B");
				          printf("\t%s\n",temp.time);
					      printf("\t %s   \t%s\n",temp.name,temp.msg);
					   printf("\033[14A");
					   printf("\033[36C");
				   }
				   break;
			   }
		   case SMILE:
			   {
				   if(temp.revert == MYFLAGNO)
				   {
					   printf("\n\t\t\t您被禁言了，请联系管理员\n");
				   }
				   else
				   {
					   printf("\n\t\t\t****************聊天对话框***********\n");
				          printf("\n\t\t\t%s\n",temp.time);
					      printf("\t\t\t%s给大家发了一个%s\n",temp.name,temp.msg);
					   printf("\t\t\t***********************************\n");
				   }
				   break;
			   }
		   case WELCOME:
			   {
				   if(temp.revert == MYFLAGNO)
				   {
					   printf("\n\t\t\t您被禁言了，请联系管理员\n");
				   }
				   else
				   {
					   printf("\n\t\t\t****************聊天对话框***********\n");
				       printf("\n\t\t\t%s\n",temp.time);
					   printf("\t\t\t%s给大家说：%s\n",temp.name,temp.msg);
					   printf("\t\t\t***********************************\n");
				   }
				   break;
			   }
			case PASSWD:
			   {
				   if(temp.revert == 1)
				   {
					   printf("\n\t\t\t修改密码完成,系统将自动退出，请您重新登陆，谢谢合作！\n");
					   sleep(2);
					   exit(1);
				   }
				   else if(temp.revert == 0)
				   {
					   printf("\n\t\t\t修改密码失败\n");
				   }
				   else
				   {
					   printf("\n\t\t\t服务器给你发送了未知的信息\n");
				   }
				   break;
			   }
			case CHANGE:
			   {
	              if(temp.revert == REGNO)
 	                  {
	 	                 printf("\t\t\t\t已有账户使用此用户名！\n");
	                  }
				  else if(temp.revert == 1)
				   {
					   printf("\n\t\t\t修改用户名完成,系统将自动退出，请您重新登陆，谢谢合作！\n");
					   sleep(2);
					   exit(1);
				   }
				   else if(temp.revert == 0)
				   {
					   printf("\n\t\t\t修改用户名失败\n");
				   }
				   else
				   {
					   printf("\n\t\t\t服务器给你发送了未知的信息\n");
				   }
				   break;
			   }
			  case BOOT:
			   {
				   if(temp.revert == ONLINEOUT)
				   {
					   printf("\n\t\t\t您要踢的用户已经不在本聊天室了！\n");
				   }
				   else if(temp.revert == BOOTOK)
				   {
					   printf("\n\t\t\t管理员请您离开本聊天室！2秒后，客户端退出，如有问题，请联系管理员\n");
					   sleep(2);
					   exit(1);
				   }
				   else
				   {
					   printf("\n\t\t\t服务器给你发送了未知的信息\n");
				   }
				   break;
			   }
			  case STEP:
			   {
				   if(temp.revert == ONLINEOUT)
				   {
					   printf("\n\t\t\t您要禁言的用户已经不在本聊天室了！\n");
				   }
				   else if(temp.revert == 0)
				   {
					   printf("\n\t\t\t禁言失败！请察看服务器！\n");
				   }
				   else if(temp.revert == 1)
				   {
				          printf("\n\t\t\t%s\n",temp.time);
					   printf("\n\t\t\t您已经被禁言了，请联系管理员\n");
				   }
				   else
				   {
					   printf("\n\t\t\t服务器向您发送了未知信息\n");
				   }
				   break;
			   }
			  case BAN:
			   {
				   if(temp.revert == ONLINEOUT)
				   {
					   printf("\n\t\t\t您要解禁的用户已经不在本聊天室了！\n");
				   }
				   else if(temp.revert == TOFLAGOK)
				   {
					   printf("\n\t\t\t对方可以说话不需要解禁！\n");
				   }
				   else if(temp.revert == 0)
				   {
					   printf("\n\t\t\t解禁失败！请察看服务器！\n");
				   }
				   else if(temp.revert == 1)
				   {
				          printf("\n\t\t\t%s\n",temp.time);
					   printf("\n\t\t\t您已经被解禁，可以继续聊天了哦！\n");
				   }
				   else
				   {
					   printf("\n\t\t\t服务器向您发送了未知信息\n");
				   }
				   break;
			   }
			  case SET:
			   {

				   if(temp.revert == 1)
				   {
                      printf("\n\t\t\t%s该用户已经被您注销了！\n",temp.toname);
				   }
				   else if(temp.revert == ONLINEIN)
				   {
					   printf("\n\t\t\t对方在线，请先把对方提出本聊天室后再注销该用户!\n");
				   }
				   else if(temp.revert == 0)
				   {
					   printf("\n\t\t\t注销失败，可能不存在此用户\n");
				   }
				   else
				   {
					   printf("\n\t\t\t服务器向您发送了未知信息\n");
				   }

				   break;
			   }
			  case SEE:
			   {
				   printf("\n\t\t\t\t%s在线!\n",temp.msg);
				   break;
			   }
			  case DATA:
			   {
				  printf("\n\t\t\t\t********************************************");
				  printf("\n\t\t\t\t%s\n\t\t\t\t%s",temp.time,temp.msg);
				  printf("\n\t\t\t\t****************   end    ******************"); 
				  break;
			   }
			  case SEND:				  
			   {
				   if(temp.revert == ONLINEOUT)
				   {
					   printf("\n\t\t\t您发送的对象不在线");
				   }
				   else if(temp.revert == SENDOK)
				   {
				          printf("\n\t\t\t%s\n",temp.time);
					   printf("\n\t\t\t\t%s向您发送文件名：%s\n",temp.name,temp.filename);
						 int num;
						 int file;
						 char data[50];
						 sprintf(data,"./temp/%s",temp.filename);
					     file = open(data,O_CREAT|O_RDWR|O_NONBLOCK,S_IWUSR);
						 if(file == -1 )
						 {
							 printf("\t\t\t文件打开失败！\n");
						 }
						 else
						 {
						       lseek(file,0,SEEK_SET);
						       num =  write(file,temp.msg,strlen(temp.msg));
							   if(num == -1)
							   {
								   printf("\t\t\t文件写入失败\n");
							   }
							   else
							   {
								   printf("\t\t\t文件接收成功，请在temp目录下查找对方传过来的文件！\n");
							   }
						 }
						 close(file);
				  }
				   else
				   {
						   printf("服务器未向您发送一个正确的信号！");
				   }
				   break;
			   }
	   }
	   memset(&temp,0,sizeof(stChat));
	}
}
