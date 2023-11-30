#include<unistd.h>

#include<stdio.h>

int main(){

	//write(1,"hello work",10);

	//write(1,"hello work",2);

	//write(1,"hello work",20);

	int n ;

	n =write(1, "hello\n", 6);

	printf("the value of n in %d",n);

}