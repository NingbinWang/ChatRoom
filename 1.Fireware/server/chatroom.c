#include"data.h"
#include"package.h"
void display(stChat temp)//用于显示发送命令
{
	printf("name = %s\n",temp.name);
	printf("passwd = %s\n",temp.passwd);
	printf("cmd = %d\n",temp.cmd);
	printf("revert = %d\n",temp.revert);
    printf("toname = %s\n",temp.toname);
	printf("msg = %s\n",temp.msg);
	printf("flag = %d\n",temp.flag);
	printf("sockfd = %d\n",temp.sockfd);
	printf("time = %s\n",temp.time);
	printf("filename = %s\n",temp.filename);
}
int main()
{
	time_t timep;
	time(&timep);
	char *timedata = ctime(&timep);
	sqlite3 *db = NULL;
	char *errmsg;
	open_db(&db);//打开数据库
    creat_user_db(db,&errmsg);
    creat_data_db(db,&errmsg);
    creat_online_db(db,&errmsg);
    creat_server_db(db,&errmsg);
    insert_server_db(db,timedata,&errmsg);//向server数据库插入数据
	insert_server();
    int  lfd;
	int cfd;
	int sfd;
	int rdy;
    stChat temp;
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int client[FD_SETSIZE];  /* 客户端连接的套接字描述符数组 */
	int maxi;
	int maxfd;                        /* 最大连接数 */
	fd_set rset;
	fd_set allset;
	socklen_t addr_len;         /* 地址结构长度 */
	int i;
	int n;
	int len;
	int opt = 1;   /* 套接字选项 */
	char addr_p[20];
    mybzero(&sin);
    lfd = mysocket();
	/*设置套接字选项 使用默认选项*/
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    mybind(lfd,&sin);	// 调用bind函数 将serer_addr结构绑定到sockfd上 
    mylisten(lfd);// 开始监听端口   等待客户的请求
	printf("\t\t\t服务器开始等待客户端链接\n");
	maxfd = lfd;                                /*对最大文件描述符进行初始化*/
	maxi = -1;
	/*初始化客户端连接描述符集合*/
	for(i = 0;i < FD_SETSIZE;i++)
	{
        client[i] = -1;
	}

	FD_ZERO(&allset);                     /* 清空文件描述符集合 */
	FD_SET(lfd,&allset);                    /* 将监听字设置在集合内 */
	/* 开始服务程序的死循环 */
	while(1)
	{
		rset = allset;
        
		/*得到当前可以读的文件描述符数*/
		rdy = select(maxfd + 1, &rset, NULL, NULL, NULL);
		
		if(FD_ISSET(lfd, &rset))
		{
		
			addr_len = sizeof(sin);
            cfd = myaccept(lfd,&cin,&addr_len);// 接受客户端的请求 
            /*查找一个空闲位置*/
			for(i = 0; i<FD_SETSIZE; i++)
			{       //printf("%d\t",client[i]);
				if(client[i] <= 0)
				{
					client[i] = cfd;   /* 将处理该客户端的连接套接字设置到该位置 */
					break;
				}
			}

		/* 太多的客户端连接   服务器拒绝俄请求  跳出循环 */
			if(i == FD_SETSIZE)
			{
				printf("too many clients");
				exit(1);
			}

			FD_SET(cfd, &allset);     /* 设置连接集合 */

			if(cfd > maxfd)                  /* 新的连接描述符 */
			{
				maxfd = cfd;
			}

			if(i > maxi)
			{
				maxi = i;
			}

			if(--rdy <= 0)                /* 减少一个连接描述符 */
			{
				continue;
			}

		}
        
		/* 对每一个连接描述符做处理 */
		for(i = 0;i< FD_SETSIZE;i++)
		{   
			if((sfd = client[i]) < 0)
			{
				continue;
			}

			if(FD_ISSET(sfd, &rset))
			{
			    printf("客户端sfd = %d已经成功链接\n",sfd);
				n = read(sfd,&temp,sizeof(stChat));
				if(n == 0)
				{
					printf("客户端sfd = %d已经离开本服务器. \n",sfd);
				   	delete_online_db(db,&errmsg,sfd);
					fflush(stdout);                                    /* 刷新 输出终端 */
					close(sfd);
					FD_CLR(sfd, &allset);                        /*清空连接描述符数组*/
					client[i] = -1;
				}
				else
				{
					temp.sockfd = sfd;
					/* 将客户端地址转换成字符串 */
					inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));
					addr_p[strlen(addr_p)] = '\0';
					/*打印客户端地址 和 端口号*/
					printf("客户端的Ip是%s, 端口是 %d\n",addr_p,ntohs(cin.sin_port));
                    int revert ;
					revert = cmd_user(db,&errmsg,&temp,sfd);
					temp.revert = revert;
					printf("开始向客户端发送命令!\n");
				//	printf("以下为命令结构体！\n");
                 //   display(temp);
				    if(revert < 5)
					{  
                         mywrite(&temp);
					}
					else if(revert == DATAOK)
					{
                        read_data(db,&errmsg,&temp);//向在线用户发送信息
					}
					else if(revert == SEEOK)
					{
                         read_online_all(db,&errmsg,&temp);//向在线用户发送信息
					}
					else if(revert == ALLOK || revert == SMILEOK || revert == WELCOMEOK)
					{
                         write_online_all(db,&errmsg,&temp);
					}
					printf("发送完毕!\n");
					memset(&temp,0,sizeof(stChat));//清空发送数据结构体
					/* 谐函数出错 */
					if(n == 1)
					{
						exit(1);
					}
				}

				/*如果没有可以读的套接字   退出循环*/
				if(--rdy <= 0)
				{
					break;
				}


			}
		}

	}

	close(lfd);       /* 关闭链接套接字 */
	return 0;
}
