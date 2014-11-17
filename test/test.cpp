/*-----------------------------------------------------------------------
** File Name: test.cpp
** ID:5130379059
** Name: Jin Jianian
** Created Time: 2014年11月11日 星期二 22时44分31秒
** ----------------------------------------------------------------------
*/
#include<cstdio>
#include<cstring>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
//#include <process.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
	int fd1,fd2,fd3,fd4,fd5,fd6;
	int status;
	pid_t pid;
	char c;
	fd1 = open("foo.txt",O_RDONLY,0);
	fd2 = open("foo.txt",O_RDONLY,0);
	fd3 = open("bar.txt",O_RDWR,0);
	fd4 = open("bar.txt",O_RDWR,0);
	fd5 = open("baz.txt",O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
	fd6 = dup(STDOUT_FILENO);
	dup2(fd5,STDOUT_FILENO);
	if((pid = fork())==0){
		dup2(fd3,fd2);
		read(fd3,&c,1);printf("%c",c);
		write(fd4,"!@#$%^",6);
		read(fd3,&c,1);printf("%c",c);
		read(fd1,&c,1);printf("%c",c);
		read(fd2,&c,1);printf("%c\n",c);
		exit(0);
	}
	wait(NULL);
	read(fd2,&c,1);printf("%c\n",c);
	fflush(stdout);
	dup2(fd6,STDOUT_FILENO);
	printf("done.\n");
	return 0;
}
