#include"data.h"
int cmd_user(sqlite3 *db,char **errmsg,vpChat temp,int sockfd)//用语判别用户信息
{
	int flag;
	int sayflag;
	printf("cmd = %d\n",temp->cmd);
   switch(temp->cmd )
   {
    case REG:
		  {
	         flag = read_user(db,errmsg,temp->name);
	         if(flag == USERIN)
	         {
		         return REGNO;//注册重名
	         }
	          else
	         {
                reg_db(db,errmsg,temp->name,temp->passwd);
                temp->flag = read_id(db,errmsg,temp->name);
                return REGOK;
	         }
		     break;
		  }
     case LOG:
		  {
			  int flagpasswd;
			  flag = read_online_ok(db,errmsg,temp->name);
			  if(flag == ONLINEIN)
			  {
				  return ONLINEIN;
			  }
			  else
			  {
				  flagpasswd = read_pass(db,errmsg,temp->name,temp->passwd);
				  if(flagpasswd == PASSWDOK)
				  {
                      log_db(db,errmsg,temp->name,sockfd);
					  return PASSWDOK;
				  }
				  else
				  {
					  return PASSWDNO;
				  }
			  }
			  break;
		  }  
     case LOGID:
		  {
			  int flagpasswd;
              read_id_name(db,errmsg,temp);//询问有无此用户
			  flag = read_online_ok(db,errmsg,temp->name);
			  if(flag == ONLINEIN)
			  {
				  return ONLINEIN;
			  }
			  else
			  {
				  flagpasswd = read_pass(db,errmsg,temp->name,temp->passwd);
				  if(flagpasswd == PASSWDOK)
				  {
                      log_db(db,errmsg,temp->name,sockfd);
					  return PASSWDOK;
				  }
				  else
				  {
					  return PASSWDNO;
				  }
			  }
			  break;
		  }  
	  case CHAT:
		   {
			   int tempfd;
              tempfd = read_online_fd(db,errmsg,temp->toname);
			  if(tempfd == ONLINEOUT)
			  {
                   return ONLINEOUT;
			  }
			  else
			  {
                  sayflag = read_online_flag(db,errmsg,temp->name); 
				  if(sayflag == 0)
				  {
					  return MYFLAGNO;
				  }
				  else
				  { 
                     temp->flag = flag;
					 temp->sockfd = tempfd;
					 insert_data_db(db,errmsg,temp->time,temp);
				     return CHATOK;
				  }
			  }
		      break;
		   }
	  case ALL:
		   {
               sayflag = read_online_flag(db,errmsg,temp->name); 
			   if(sayflag == 0)
			   {

				   return MYFLAGNO;
			   }
			   else
			   {
				   insert_data_db(db,errmsg,temp->time,temp);
			       return ALLOK;
			   }
			   break;
		   }
	  case SMILE:
		   {
               sayflag = read_online_flag(db,errmsg,temp->name); 
			   if(sayflag == 0)
			   {
				   return MYFLAGNO;
			   }
			   else
			   {
					 insert_data_db(db,errmsg,temp->time,temp);
			       return SMILEOK;
			   }
			   break;
		   }
       case WELCOME:
		   {
               sayflag = read_online_flag(db,errmsg,temp->name); 
			   if(sayflag == 0)
			   {
				   return MYFLAGNO;
			   }
			   else
			   {
					 insert_data_db(db,errmsg,temp->time,temp);
			       return WELCOMEOK;
			   }
			   break;
		   }
	   case PASSWD:
		   {
             flag =  update_passwd(db,errmsg,temp->name,temp->passwd);
             return flag;
			 break;
		   }
	   case BOOT:
		   {  
			  int tempfd;
              tempfd = read_online_fd(db,errmsg,temp->toname);
			  if(tempfd == ONLINEOUT)
			  {
                   return ONLINEOUT;
			  }
			  else
			  {
					 temp->sockfd = tempfd;
					 return BOOTOK;
			  }
			  break;
		   }
		case STEP:
		   {
			  int tempfd;
              tempfd = read_online_fd(db,errmsg,temp->toname);
			  if(tempfd == ONLINEOUT)
			  {
                   return ONLINEOUT;
			  }
			  else
			  {
                     flag =  update_flag(db,errmsg,temp->toname,0);
					 if(flag == 1)
					 {
					    temp->sockfd = tempfd;
					 }
					 return flag;
			  }
			  break;
		   }
	    case BAN:
		   {

			  int tempfd;
              tempfd = read_online_fd(db,errmsg,temp->toname);
			  if(tempfd == ONLINEOUT)
			  {
                   return ONLINEOUT;
			  }
			  else
			  {
                     sayflag = read_online_flag(db,errmsg,temp->toname); 
					 if(sayflag == 1)
					 {
						 return TOFLAGOK;
					 }
					 else
					 {
                         flag =  update_flag(db,errmsg,temp->toname,1);
					     if(flag == 1)
					     {
					            temp->sockfd = tempfd;
					     }
					     return flag;
					 }
			  }
			  break;
		   }
		  case SET:
		   {

			  int tempfd;
              tempfd = read_online_fd(db,errmsg,temp->toname);
			  if(tempfd == ONLINEOUT)
			  {
                  flag = delete_user(db,errmsg,temp->toname);
    			  return flag;
			  }
			  else
			  {
				  return ONLINEIN;
			  }
			   break;
		   }
		  case SEE:
		   {
			   return SEEOK;
			   break;
		   }
		  case DATA:
		   {
               return DATAOK;
			   break;
		   }
		  case SEND:
		   {
			  int tempfd;
              tempfd = read_online_fd(db,errmsg,temp->toname);
			  if(tempfd == ONLINEOUT)
			  {
    			  return ONLINEOUT;
			  }
			  else
			  {
				   temp->sockfd = tempfd;
				   return SENDOK;
			  }
			   break;
		   }
		  case CHANGE:
		   {
	         flag = read_user(db,errmsg,temp->toname);
	         if(flag == USERIN)
	         {
		         return REGNO;//注册重名
	         }
             else
			 {
                 flag = update_user(db,errmsg,temp->name,temp->toname);//¿¿¿¿
                 if(flag == 1)
				 {
                      sayflag = update_db_data(db,errmsg,temp->name,temp->toname);//修改密码
                     return sayflag;
				 }
				 else
				{
					return 0;
				}
			 }
			   break;
		   }

   }
}
