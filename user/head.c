#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
int main(int a,char **argc){
	if(a==1){
	   printf("less_arguments\n");
	   exit(1);
	}
	int fd=open(argc[1],O_RDONLY);
	if(fd<0){
	   printf("File doesnt exist\n");
	   exit(1);
	}
	int n;
	if(a==3){
	 n=atoi(argc[2]);
	}
	else{
	   n=10;
	}
	char ch;
	int buf;
	int line=0;
	while((buf=read(fd,&ch,1))>0){
		write(1,&ch,buf);
		if(ch=='\n'){
		    line=line+1;
		    if(line==n){
		    	break;
		    }
		
		}
	}
	exit(0);

}
