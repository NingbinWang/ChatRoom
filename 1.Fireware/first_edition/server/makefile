main = insert.o chatroom.o sql.o passwd.o string.o cmd.o socket.o
ebook:$(main)
	@gcc $(main) -o chatroom -lsqlite3
passwd.o: passwd.c
	@gcc passwd.c -c
insert.o: insert.c	
	@gcc insert.c -c
sql.o:sql.c
	@gcc sql.c -c
string.o:string.c
	@gcc string.c -c
cmd.o:cmd.c
	@gcc cmd.c -c
socket.o:socket.c
	@gcc socket.c -c
.PHONY: clean cleanall
clean:
	@rm *.o
cleanall:
	@rm *.o  chatroom
