#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int a,char **arg){
	int pid=fork();
	if(a<=1){
	     
	    exit(1);
	}
	if(pid<0){
	     exit(1);
	}
	else if(pid==0){
		exec(arg[1],&arg[1]);
		exit(1);
	}
	else{
		wait(0);
	}
}
