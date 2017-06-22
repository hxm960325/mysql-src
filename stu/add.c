#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * headname = "head.html";
char * footname = "footer.html";

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	FILE * fd;
	char sid[12] ="\0";
	char sname[32] = "\0";
	char sex[32] = "\0";
	char age[2] = "\0";
	char scid[4] = "\0";
	int status = 0;
	char ch;

	if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
	fclose(fd);

	status = cgiFormString("sid",  sid, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sid error!\n");
		return 1;
	}

	status = cgiFormString("sname",  sname, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sname error!\n");
		return 1;
	}

	status = cgiFormString("sex",  sex, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sex error!\n");
		return 1;
	}

	status = cgiFormString("age",  age, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get age error!\n");
		return 1;
	}

	status = cgiFormString("scid",  scid, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scid error!\n");
		return 1;
	}

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

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
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}



	sprintf(sql, "insert into information(sid,sname,sex,age,scid) values('%s', '%s', '%s', %d, '%s')", sid, sname, sex, atoi(age), scid);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "<div class=\"container\"> <h1 class=\"text-center\">成功添加学生信息！</h1>");
	mysql_close(db);
	return 0;
}
