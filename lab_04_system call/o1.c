

#include<unistd.h>

#include<fcntl.h>

#include<sys/types.h>

#include<sys/stat.h>



int main(){

	int n,fd,fd1;

	char buf[50];

	//fd = open ("text.txt",O_RDONLY);

	n = read(fd,buf,10);

	fd1 = open("target.txt",O_WRONLY|O_APPEND);

	//fd1 = open("target.txt",O_CREAT|O_WRONLY,0642);

	write(fd1,buf,n);

}