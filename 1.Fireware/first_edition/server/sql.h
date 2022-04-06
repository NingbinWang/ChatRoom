void is_sqlite(int rc);  //²âÊÔÊı¾İ¿â
void is_malloc_ok(vpChat *list);
void is_sqlite_ok(int rc);
void open_db(sqlite3 **db);//´ò¿ªÊı¾İ¿â
void creat_user_db(sqlite3 *db,char **errmsg);//½¨Á¢userÊı¾İ±í
void creat_data_db(sqlite3 *db,char **errmsg);//½¨Á¢dataÊı¾İ±í
void creat_online_db(sqlite3 *db,char **errmsg);//½¨Á¢onlineÊı¾İ±í
void creat_server_db(sqlite3 *db,char **errmsg);//½¨Á¢serverÊı¾İ±í
void insert_server_db(sqlite3 *db,char *time,char **errmsg);//¿server¿¿¿¿¿¿¿
void read_db_ok(sqlite3 *db,char *errmsg,char*tablename);//¿¿¿¿¿¿¿
void delete_clean_db(sqlite3 *db,char *tablename,char **errmsg);
int read_online_fd(sqlite3 *db,char **errmsg,char *user);//¿¿¿¿¿¿
int read_online_flag(sqlite3 *db,char **errmsg,char *user);//¿¿¿¿¿¿
void write_online_all(sqlite3 *db,char **errmsg,vpChat temp);
int update_passwd(sqlite3 *db,char **errmsg,char *name,char *passwd);
void insert_data_db(sqlite3 *db,char **errmsg,char *time,vpChat temp);
int update_flag(sqlite3 *db,char **errmsg,char *name,int flag);
int delete_user(sqlite3 *db,char **errmsg,char *name);
void read_online_all(sqlite3 *db,char **errmsg,vpChat temp);//¿¿¿¿¿¿¿¿¿
void read_data(sqlite3 *db,char **errmsg,vpChat temp);//¿¿¿¿¿¿¿¿¿
int update_user(sqlite3 *db,char **errmsg,char *name,char *toname);//¿¿¿¿
int update_db_data(sqlite3 *db,char **errmsg,char *name,char *toname);//¿¿¿¿
