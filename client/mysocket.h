
int mysocket();
void mybezero(struct sockaddr_in *server_addr,struct hostent *host);
void myconnect(int sockfd,struct sockaddr_in *server_addr);
void mywrite(int sockfd,vpChat temp);
