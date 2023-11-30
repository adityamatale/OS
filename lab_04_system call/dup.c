#include<unistd.h>

#include<stdio.h>

#include<fcntl.h>

#include<sys/types.h>

#include<sys/stat.h>



int main(){

	int fd, fd1, fd2;

	fd = open("dup",O_RDONLY);

	printf("OLD file descriptor %d\n",fd);

	fd1 = dup(fd);

	fd2 = dup2(fd,7);

	printf("NEW file descriptor %d\n",fd1);

	printf("NEW file descriptor again %d\n",fd2);



}