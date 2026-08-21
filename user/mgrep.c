#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int matchhere(char *re, char *text);
int matchstar(int c, char *re, char *text);

int match(char *re, char *text)
{
  if (re[0] == '^')
    return matchhere(re + 1, text);

  do {
    if (matchhere(re, text))
      return 1;
  } while (*text++ != '\0');

  return 0;
}

int matchhere(char *re, char *text)
{
  if (re[0] == '\0')
    return 1;

  if (re[1] == '*')
    return matchstar(re[0], re + 2, text);

  if (re[0] == '$' && re[1] == '\0')
    return *text == '\0';

  if (*text != '\0' &&
      (re[0] == '.' || re[0] == *text))
    return matchhere(re + 1, text + 1);

  return 0;
}

int matchstar(int c, char *re, char *text)
{
  do {
    if (matchhere(re, text))
      return 1;
  } while (*text != '\0' &&
           (*text++ == c || c == '.'));

  return 0;
}
int main(int a,char **arg){
	if(a<3){
	     printf("Not enough arguments\n");
	     exit(1);
	}
	for(int i=0;i<a-2;i++){
	    int pid=fork();
	    if(pid==0){
	    	int fd=open(arg[i+2],O_RDONLY);
		if(fd<0){
	           printf("File %s not available\n",arg[i+2]);
		   exit(1);
		}
		char ch;
		char p[512];
		int idx=0;
		while(read(fd,&ch,1)>0){
		       if(ch=='\n'){
			  p[idx]='\0';
		       	  if(match(arg[1],p)){
			  	printf("(Worker PID: %d) %s\n",getpid(),p);
			  }
			  idx=0;
		       }
		       else{
			  p[idx++]=ch;
		       }
		}
		if(idx>0){
		   p[idx]='\0';
		   if(match(arg[1],p)){
		  	printf("(Worker PID: %d) %s\n",getpid(),p); 
		   }

		}
		close(fd);
		exit(0);
	    
	    }
	    else{
	    	wait(0);
		printf("\n");
	    
	    }
	}
}
