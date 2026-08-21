#include "kernel/types.h"
#include "user/user.h"

int main(){
	printf("initial child count: %d\n",get_child_count());
	int pid1=fork();
	//printf("child_count after forking: %d\n",get_child_count());
	if(pid1==0){
	   pause(100);
	   exit(0);
	}
	else{
	printf("child_count after forking: %d\n",get_child_count());
	}
	int pid2=fork();
	//printf("child_count after forking again: %d\n",get_child_count());
	if(pid2==0){
	    pause(99);
    	    exit(0);
	}
	else{
	printf("child_count after forking again: %d\n",get_child_count());
	}
	printf("child_count of pid %d: %d\n",getpid(),get_process_child_count(getpid()));
	wait(0);
	printf("child reaped. new child count: %d\n",get_child_count());
	wait(0);
	printf("child reaped. new child count: %d\n",get_child_count());


}
