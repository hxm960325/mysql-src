CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi fdel.cgi stu_login.cgi teacher_login.cgi selscore.cgi wscore.cgi selcourse.cgi tcourse.cgi stu_course.cgi 

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
		cp *.cgi /usr/lib/cgi-bin/sx
		cp head.html footer.html stu.html teacher.html /usr/lib/cgi-bin/sx/
