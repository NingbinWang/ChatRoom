#include"data.h"
void reg_db(sqlite3 *db,char **errmsg,char *name,char *passwd)//注册插入
{
	char sql[1024];
	int rc;
	sprintf(sql,"insert into user(name,passwd)values('%s','%s')",name,passwd);
	rc = sqlite3_exec(db,sql,NULL,NULL,errmsg);
	is_sqlite(rc);
}
void log_db(sqlite3 *db,char **errmsg,char *name,int sockfd)//登陆插入
{
	char sql[1024];
	int rc;
	sprintf(sql,"insert into online(name,socket,flag)values('%s',%d,1)",name,sockfd);
	rc = sqlite3_exec(db,sql,NULL,NULL,errmsg);
	is_sqlite(rc);
}
void delete_online_db(sqlite3 *db,char **errmsg,int sockfd)//删除登陆
{
	char sql[1024];
	int rc;
	sprintf(sql,"delete from online where socket = %d",sockfd);
	rc = sqlite3_exec(db,sql,NULL,NULL,errmsg);
	is_sqlite(rc);
}
int read_user(sqlite3 *db,char **errmsg,char *user)//询问有无此用户
{
	int rc;
	int i;
	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare(db,"select * from user",-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int userflag = 1;
    while(rc == SQLITE_ROW)
	{
       userflag = my_strcmp(user,sqlite3_column_text(stmt,1));
	   if(userflag == 0 )
	   {
			return USERIN;
	   }	
	   rc = sqlite3_step(stmt);
	}
	return USEROUT;
}
int read_id(sqlite3 *db,char **errmsg,char *user)//询问有无此用户
{
	int rc;
	int i;
	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare(db,"select * from user",-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int userflag = 1;
    while(rc == SQLITE_ROW)
	{
       userflag = my_strcmp(user,sqlite3_column_text(stmt,1));
	   if(userflag == 0 )
	   {
        	return atoi(sqlite3_column_text(stmt,0));
	   }	
	   rc = sqlite3_step(stmt);
	}
	return USEROUT;
}
void read_id_name(sqlite3 *db,char **errmsg,vpChat temp)//询问有无此用户
{
	int rc;
	int i;
	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare(db,"select * from user",-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int userflag = 1;
    while(rc == SQLITE_ROW)
	{
       userflag = my_atoi(sqlite3_column_text(stmt,0));
	   if(userflag == temp->flag )
	   {
		   my_strcpy(temp->name,sqlite3_column_text(stmt,1));
	   }	
	   rc = sqlite3_step(stmt);
	}
}
int read_pass(sqlite3 *db,char **errmsg,char *user,char *passwd)//用于用户验证
{
	int rc;
	int i;
	sqlite3_stmt *stmt = NULL;
	rc = sqlite3_prepare(db,"select * from user",-1,&stmt,0); 
    is_sqlite_ok(rc);
	rc = sqlite3_step(stmt);
	int userflag = 1;
	int passwdflag = 1;
    while(rc == SQLITE_ROW)
	{
       userflag = my_strcmp(user,sqlite3_column_text(stmt,1));
       passwdflag = my_strcmp(passwd,sqlite3_column_text(stmt,2));
	   if(userflag == 0 && passwdflag == 0)
	   {
			return PASSWDOK;
	   }	
	   rc = sqlite3_step(stmt);
	}
	return PASSWDNO;
}
int read_online_ok(sqlite3 *db,char **errmsg,char *user)//用于验证在线用户
{
	int rc;
	int i;
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
			return ONLINEIN;
	   }	
	   rc = sqlite3_step(stmt);
	}
	return ONLINEOUT;
}
