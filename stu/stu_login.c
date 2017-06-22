#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * headname = "head.html";
char * stulogin = "stu.html";
char * footname = "footer.html";

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	fprintf(cgiOut, "<head><meta charset=\"utf-8\"><title>查询结果</title>\
		    <link rel=\"stylesheet\" href=\"/stu/public/css/bootstrap.min.css\">\
		</head>");

	FILE * fd;
	char ch;
	char sid[32] = "\0";
	int status= 0;

	status = cgiFormString("sid",  sid, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sid error!\n");
		return 1;
	}

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	sprintf(sql, "select * from information where sid='%s' ",sid);

	//初始化
	db = mysql_init(NULL);
	mysql_options(db, MYSQL_SET_CHARSET_NAME, "utf8");
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	MYSQL_RES *res;
	res = mysql_store_result(db);
	if (res == NULL)
	{
		fprintf(cgiOut,"mysql_store_result fail:%s\n", mysql_error(db));
		return -1;
	}

	int num = (int)res->row_count;
	if(num){
		if(!(fd = fopen(stulogin, "r"))){
			fprintf(cgiOut, "Cannot open file, %s\n", stulogin);
			return -1;
		}
		ch = fgetc(fd);

		while(ch != EOF){
			fprintf(cgiOut, "%c", ch);
			ch = fgetc(fd);
		}
	}else{
		if(!(fd = fopen(headname, "r"))){
			fprintf(cgiOut, "Cannot open file, %s\n", headname);
			return -1;
		}
		ch = fgetc(fd);

		while(ch != EOF){
			fprintf(cgiOut, "%c", ch);
			ch = fgetc(fd);
		}
		fprintf(cgiOut, "<div class=\"container\"> <h1 class=\"text-center\">该学生不存在！</h1>");
	}
	mysql_close(db);
	return 0;
}
