#include<unistd.h>

#include<stdio.h>

int main(){

	int n ;

	char b[30];

	n = read(0,b,10);

	write(1,b,n);

	write(1,b,n);

	printf("2");

}