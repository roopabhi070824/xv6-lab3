#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
int main(int a,char **arg){
       if(a==3){
       	  int fd=open(arg[1],O_RDONLY);
	  if(fd<0){
	       exit(1);
	  }
	  int fd1=open(arg[2],O_WRONLY|O_CREATE);
	  if(fd1<0){
	  	exit(1);
	  }
	  int n;
	  char buff[1024];
	  while((n=read(fd,buff,sizeof(buff)))>0){
	  	if(write(fd1,buff,n)>0){
		     exit(1);
		}
	  }
	close(fd);
	close(fd1);
       }
       else{
	       exit(1);
       }
}
