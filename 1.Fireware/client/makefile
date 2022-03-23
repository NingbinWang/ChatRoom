main = insert.o client.o  passwd.o string.o cmd.o process.o pthread.o socket.o get_passwd.o
ebook:$(main)
	@gcc $(main) -o client -lsqlite3 -lpthread
passwd.o: passwd.c
	@gcc passwd.c -c
insert.o: insert.c	
	@gcc insert.c -c
string.o:string.c
	@gcc string.c -c
cmd.o:cmd.c
	@gcc cmd.c -c
process.o:process.c
	@gcc process.c -c
pthread.o:pthread.c
	@gcc pthread.c -c
socket.o:socket.c
	@gcc socket.c -c
get_passwd.o:get_passwd.c
	@gcc get_passwd.c -c
.PHONY: clean cleanall
clean:
	@rm *.o
cleanall:
	@rm *.o  client
