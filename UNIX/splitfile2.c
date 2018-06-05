#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

char fileprefix[100];
char newfile[120];
char integer[20];

int cret(int);


int main(int argc,char **argv)
{

	int fd1,fd2,n,i;
	ssize_t lenr,lenw;
	pid_t pid;

	fd1=open(argv[1],O_RDONLY);

	memset(fileprefix,'\0',sizeof(fileprefix));
	memset(newfile,'\0',sizeof(newfile));
	memset(integer,'\0',sizeof(integer));


	strcpy(fileprefix,argv[1]);
	char c[2]=".";
	strcat(fileprefix,c);

	if(lseek(fd1,0,SEEK_SET) == -1) printf("Seek fail\n");

	char buff[10000];   // default stack size is around 8MB
	memset(buff,'\0',sizeof(buff));

	i=0;

	while((lenr = read(fd1,buff,10000))>0 && ++i){
	    if((pid=fork())==0){
		cret(i);
		fd2=open(newfile,O_WRONLY | O_CREAT,00777);
		lenw=write(fd2,buff,lenr);
		close(fd2);
		exit(0);
		}
	    else
		wait(NULL);	    	
	}
	close(fd1);	
	exit(0);
}

	
int cret(int x){
	sprintf(integer,"%d",x);	
	strcpy(newfile,fileprefix);
	strcat(newfile,integer);
	return 0;
}

	




