
void mybzero(struct sockaddr_in *sin);
int mysocket();
void mybind(int lfd,struct sockaddr_in *sin);	// 调用bind函数 将serer_addr结构绑定到sockfd上 
void mylisten(int lfd);// 开始监听端口   等待客户的请求
int myaccept(int lfd,struct sockaddr_in *cin,socklen_t * addr_len);// 接受客户端的请求 
void mywrite(vpChat temp);
