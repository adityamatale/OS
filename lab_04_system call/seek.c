#include<unistd.h>

#include<sys/types.h>

#include<fcntl.h>

#include<sys/stat.h>



int main(){

	int n, f, f1;

	char buf[10];

	f = open("seeking.txt",O_RDWR);

	read(f, buf, 10);

	write(1, buf, 10);

	lseek(f,10,SEEK_CUR);

	read(f, buf, 10);

	write(1, buf, 10);



}