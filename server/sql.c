#include"data.h"
void is_malloc_ok(vpChat *list)
{
   *list = (vpChat)malloc(sizeof(stChat));
   if(*list == NULL)
   {
       exit(1); 
   }
}
void is_sqlite(int rc)  //测试数据库
{
    if(rc == SQLITE_OK)
	{
        printf("sqlite %d succse \n",__LINE__);
	}
	else
	{
		printf("数据库发生错误，请使用SQLITE3 看数据库!\n");
     	printf("sqlite %d error\n",__LINE__);
		exit(1);
	}
}

void is_sqlite_ok(int rc)
{
    if(rc == SQLITE_OK)
	{
	   printf("sqlite %d succse \n",__LINE__);
	}
	else
	{
		printf("sqlite %d error\n",__LINE__);
	}
}

void open_db(sqlite3 **db)//打开数据库
{
	int rc;
	rc = sqlite3_open("server.db",db);
	is_sqlite(rc);
}
void creat_user_db(sqlite3 *db,char **errmsg)//建立user数据表
{
	int rc;
    rc = sqlite3_exec(db,"create table user(id integer primary key autoincrement,name text,passwd text)",NULL,NULL,errmsg);
	is_sqlite_ok(rc);
}
void creat_data_db(sqlite3 *db,char **errmsg)//建立data数据表
{
	int rc;
    rc = sqlite3_exec(db,"create table data(id integer primary key autoincrement,time text,name text,toname text,msg text)",NULL,NULL,errmsg);
	is_sqlite_ok(rc);
}
void creat_online_db(sqlite3 *db,char **errmsg)//建立online数据表
{
	int rc;
    rc = sqlite3_exec(db,"create table online(id integer primary key autoincrement,name text,socket integer,flag integer)",NULL,NULL,errmsg);
	is_sqlite_ok(rc);
}
void creat_server_db(sqlite3 *db,char **errmsg)//建立server数据表
{
	int rc;
    rc = sqlite3_exec(db,"create table server(id integer primary key autoincrement,time text)",NULL,NULL,errmsg);
	is_sqlite_ok(rc);
}
void insert_server_db(sqlite3 *db,char *time,char **errmsg)//向server数据库插入数据
{
         int rc;
        char sql[1024];
	    sprintf(sql,"insert into server(time) values('%s')",time);
	    rc = sqlite3_exec(db,sql,NULL,NULL,errmsg);
	    is_sqlite(rc);
        printf("数据库已经录入完毕\n");
}
void insert_data_db(sqlite3 *db,char **errmsg,char *time,vpChat temp)//插入聊天记录
{
         int rc;
        char sql[1024];
	    sprintf(sql,"insert into data(time,name,toname,msg) values('%s','%s','%s','%s')",time,temp->name,temp->toname,temp->msg);
	    rc = sqlite3_exec(db,sql,NULL,NULL,errmsg);
	    is_sqlite(rc);
        printf("聊天记录已经录入完毕\n");
}
void delete_clean_db(sqlite3 *db,char *tablename,char **errmsg)//清空数据库
{
	char sql[1024];
	int rc;
    sprintf(sql,"delete from %s where name !='root'",tablename);
	rc = sqlite3_exec(db,"delete from student",NULL,NULL,errmsg);
	is_sqlite(rc);
}
void read_db_ok(sqlite3 *db,char *errmsg,char*tablename)//用于检测数据库
{
	int rc;
	int i;
	char sql[1024];
	sqlite3_stmt *stmt = NULL;
    sprintf(sql,"select * from %s ",tablename);
	rc = sqlite3_prepare(db,sql,-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int ncolumn;
	ncolumn = sqlite3_column_count(stmt);
                 while(rc == SQLITE_ROW)
				 {
                     for(i = 0; i < ncolumn; i++)
					 {
                         printf("%s|",sqlite3_column_text(stmt,i));
					 }
					 printf("\n");
					 rc = sqlite3_step(stmt);
				 }
}
int read_online_fd(sqlite3 *db,char **errmsg,char *user)//获取FD
{
	int rc;
	int i;
	char fd[100];
	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare(db,"select * from online",-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int userflag = 1;
    while(rc == SQLITE_ROW)
	{
       userflag = my_strcmp(user,sqlite3_column_text(stmt,1));
	   if(userflag == 0)
	   {
            my_strcpy(fd,sqlite3_column_text(stmt,2));

			return my_atoi(fd);
	   }	
	   rc = sqlite3_step(stmt);
	}
	return ONLINEOUT;
}
int read_online_flag(sqlite3 *db,char **errmsg,char *user)//用于验证是否禁言
{
	int rc;
	int i;
	char flag[10];
	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare(db,"select * from online",-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int userflag = 1;
    while(rc == SQLITE_ROW)
	{
       userflag = my_strcmp(user,sqlite3_column_text(stmt,1));
	   if(userflag == 0)
	   {
            my_strcpy(flag,sqlite3_column_text(stmt,3));

			return my_atoi(flag);
	   }	
	   rc = sqlite3_step(stmt);
	}
	return -10;
}
void write_online_all(sqlite3 *db,char **errmsg,vpChat temp)//向在线用户发送信息
{
	int rc;
  	int flag;
	char fd[100];
	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare(db,"select * from online",-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int userflag = 1;
    while(rc == SQLITE_ROW)
	{
	        flag = my_strcmp(temp->name,sqlite3_column_text(stmt,1));
            my_strcpy(fd,sqlite3_column_text(stmt,2));
			if(flag != 0)
			{
			   write( my_atoi(fd),temp,sizeof(stChat));
			}
		    sleep(1);	
	        rc = sqlite3_step(stmt);
	}
}
int update_passwd(sqlite3 *db,char **errmsg,char *name,char *passwd)//修改密码
{
         int rc;
         char sql[1024];
	     sprintf(sql,"update user set passwd = '%s'where name = '%s'",passwd,name);
	    rc = sqlite3_exec(db,sql,NULL,NULL,errmsg);
        if(rc == SQLITE_OK)
	     {
			 return 1;
	     }
	     else
	     {
			 return 0;
   	     }

}
int update_user(sqlite3 *db,char **errmsg,char *name,char *toname)//修改密码
{
         int rc;
         char sql[1024];
	     sprintf(sql,"update user set name = '%s'where name = '%s'",toname,name);
	    rc = sqlite3_exec(db,sql,NULL,NULL,errmsg);
        if(rc == SQLITE_OK)
	     {
			 return 1;
	     }
	     else
	     {
			 return 0;
   	     }

}
int update_db_data(sqlite3 *db,char **errmsg,char *name,char *toname)//修改密码
{
         int rc1;
		 int rc2;
         char sql[1024];
	     sprintf(sql,"update data set name = '%s'where name = '%s'",toname,name);
	    rc1 = sqlite3_exec(db,sql,NULL,NULL,errmsg);
		memset(sql,0,1024);
	     sprintf(sql,"update data set toname = '%s'where toname = '%s'",toname,name);
	    rc2 = sqlite3_exec(db,sql,NULL,NULL,errmsg);
        if(rc1 == SQLITE_OK && rc2 == SQLITE_OK)
	     {
			 return 1;
	     }
	     else
	     {
			 return 0;
   	     }

}
int update_flag(sqlite3 *db,char **errmsg,char *name,int flag)//禁言解禁操作
{
         int rc;
         char sql[1024];
	     sprintf(sql,"update online set flag = %d where name = '%s'",flag,name);
	    rc = sqlite3_exec(db,sql,NULL,NULL,errmsg);
        if(rc == SQLITE_OK)
	     {
			 return 1;
	     }
	     else
	     {
			 return 0;
   	     }
}
int delete_user(sqlite3 *db,char **errmsg,char *name)//注销用户
{
         int rc;
         char sql[1024];
	     sprintf(sql,"delete from user where name = '%s'",name);
	     rc = sqlite3_exec(db,sql,NULL,NULL,errmsg);
         if(rc == SQLITE_OK)
	     {
			 return 1;
	     }
	     else
	     {
			 return 0;
   	     }

}
void read_online_all(sqlite3 *db,char **errmsg,vpChat temp)//向在线用户发送信息
{
	int rc;
	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare(db,"select * from online",-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int userflag = 1;
    while(rc == SQLITE_ROW)
	{
	        my_strcpy(temp->msg,sqlite3_column_text(stmt,1));
			mywrite(temp);
		    sleep(1);	
	        rc = sqlite3_step(stmt);
    }
}
void read_data(sqlite3 *db,char **errmsg,vpChat temp)//向在线用户发送信息
{
	int rc;
	char name[80];
	char toname[80];
	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare(db,"select * from data",-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int userflag = 1;
    while(rc == SQLITE_ROW)
	{
	        my_strcpy(name,sqlite3_column_text(stmt,2));
	        my_strcpy(toname,sqlite3_column_text(stmt,3));
		if(	my_strcmp(temp->name,name) == 0)
		{
            strcat(temp->msg,"你");      
            strcat(temp->msg,"给");      
            strcat(temp->msg,toname);      
            strcat(temp->msg,"发了");      
            strcat(temp->msg,sqlite3_column_text(stmt,4));
            strcat(temp->msg,"\n");      
	        my_strcpy(temp->time,sqlite3_column_text(stmt,1));
	        mywrite(temp);
			memset(temp->msg,0,sizeof(temp->msg));
	        sleep(1);		
		}
		if(my_strcmp(temp->name,toname) == 0)
		{
            strcat(temp->msg,toname);      
            strcat(temp->msg,"给你发了");      
            strcat(temp->msg,sqlite3_column_text(stmt,4));
            strcat(temp->msg,"\n");      
	        my_strcpy(temp->time,sqlite3_column_text(stmt,1));
	        mywrite(temp);
			memset(temp->msg,0,sizeof(temp->msg));
	        sleep(1);		
		}
	        rc = sqlite3_step(stmt);
    }
}
