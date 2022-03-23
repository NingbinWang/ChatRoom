void reg_db(sqlite3 *db,char **errmsg,char *name,char *passwd);
int read_user(sqlite3 *db,char **errmsg,char *user);
int read_pass(sqlite3 *db,char **errmsg,char *user,char *passwd);//用于用户验证
int read_online_ok(sqlite3 *db,char **errmsg,char *user);
void delete_online_db(sqlite3 *db,char **errmsg,int sockfd);
int read_id(sqlite3 *db,char **errmsg,char *user);//询问有无此用户
void read_id_name(sqlite3 *db,char **errmsg,vpChat temp);//询问有无此用户
