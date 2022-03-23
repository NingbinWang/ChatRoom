#include"data.h"
int analy_cmd(char *cmd)//命令解析
{
   if(my_strcmp(cmd,"reg") == 0)
   {
	   return REG;
   }
   else if(my_strcmp(cmd,"log") == 0)
   {
	   return LOG;
   }
   else if(my_strcmp(cmd,"logid") == 0)
   {
	   return LOGID;
   }
   else if(my_strcmp(cmd,"help") == 0)
   {
       return USERHELP;
   }
   else if(my_strcmp(cmd,"exit") == 0)
   {
	   return USEREXIT;
   }
   else
   {
	   return ERROR;
   }

}
int process_root(char *cmd)//root用户命令解析
{

   if(my_strcmp(cmd,"chat") == 0)
   {
	   return CHAT;
   }
   else if(my_strcmp(cmd,"all") == 0)
   {
	   return ALL;
   }
   else if(my_strcmp(cmd,"look") == 0)
   {
	   return SMILE;
   }
   else if(my_strcmp(cmd,"welcome") == 0)
   {
	   return WELCOME;
   }
   else if(my_strcmp(cmd,"exit") == 0)
   {
	   return EXIT;
   }
   else if(my_strcmp(cmd,"help") == 0)
   {
	   return HELP;
   }
   else if(my_strcmp(cmd,"passwd") == 0)
   {
	   return PASSWD;
   }
   else if(my_strcmp(cmd,"boot") == 0)
   {
	   return BOOT;
   }
   else if(my_strcmp(cmd,"step") == 0)
   {
	   return STEP;
   }
   else if(my_strcmp(cmd,"ban") == 0)
   {
	   return BAN;
   }
   else if(my_strcmp(cmd,"set") == 0)
   {
	   return SET;
   }
   else if(my_strcmp(cmd,"see") == 0)
   {
	   return SEE;
   }
   else if(my_strcmp(cmd,"data") == 0)
   {
	   return DATA;
   }
   else if(my_strcmp(cmd,"send") == 0)
   {
	   return SEND;
   }
   else
   {
	   return ERROR;
   }
}
int process_user(char *cmd)//普通用户命令解析
{

   if(my_strcmp(cmd,"chat") == 0)
   {
	   return CHAT;
   }
   else if(my_strcmp(cmd,"all") == 0)
   {
	   return ALL;
   }
   else if(my_strcmp(cmd,"look") == 0)
   {
	   return SMILE;
   }
   else if(my_strcmp(cmd,"welcome") == 0)
   {
	   return WELCOME;
   }
   else if(my_strcmp(cmd,"exit") == 0)
   {
	   return EXIT;
   }
   else if(my_strcmp(cmd,"help") == 0)
   {
	   return HELP;
   }
   else if(my_strcmp(cmd,"passwd") == 0)
   {
	   return PASSWD;
   }
   else if(my_strcmp(cmd,"see") == 0)
   {
	   return SEE;
   }
   else if(my_strcmp(cmd,"data") == 0)
   {
	   return DATA;
   }
   else if(my_strcmp(cmd,"send") == 0)
   {
	   return SEND;
   }
   if(my_strcmp(cmd,"change") == 0)
   {
	   return CHANGE;
   }
   else
   {
	   return ERROR;
   }
}
