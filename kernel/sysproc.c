#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"


uint64 sys_square(void){
	int i;
	argint(0,&i);
	return i*i;
}

uint64 sys_nfork(void){
  int n;
  argint(0,&n);
  uint64 addr;
  int a[100];
  argaddr(1,&addr);
  for(int i=0;i<n;i++){
    int pid=kfork();
    if(pid==0){
      return 0;
    }
    else if(pid<0){
      return -1;
    }
    a[i]=pid;
  }
  if(copyout(myproc()->pagetable,myproc()->sz,addr,(char *)a,n*sizeof(int))<0){
    return -1;
  }
  return n;
}

uint64 sys_print_syscalls(void){
   struct proc *p= myproc();
   printk("Syscall counts for current process:\n");
    printk("syscall_number invocations\n");
    for(int i=1;i<SYS_MAX;i++){
      if(p->syscall_count[i]>0){
      printk("%d %ld\n",i,p->syscall_count[i]);
    }
  }
    return 0;
}


uint64 sys_print_process_syscalls(void){
  struct proc *p;
  int pid;
  argint(0,&pid);
  for(p=proc;p<&proc[NPROC];p++){
    acquire(&p->lock);
    if(p->pid==pid){
      printk("Syscall counts for pid %d\n",p->pid);
      printk("syscall_numberinvocations\n");
      for(int i=0;i<SYS_MAX;i++){
         if(p->syscall_count[i]>0){
        printk("%d %ld\n",i,p->syscall_count[i]);
      }
    }
      release(&p->lock);
      return 0;
    }
  }
  return -1;

}

uint64 sys_get_child_count(void){
	return myproc()->child_count;
}

uint64
sys_get_process_child_count(void)
{
    int pid;

    argint(0, &pid); 

    return get_process_child_count_pid(pid);
}


uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}


uint64
sys_getppid(void){
  struct proc *p=myproc();
  return p->parent->pid; 
}


uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if (t == SBRK_EAGER || n < 0) {
    if (growproc(n) < 0) {
      return -1;
    }
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if (addr + n < addr)
      return -1;
    if (addr + n > TRAPFRAME)
      return -1;
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if (n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n) {
    if (killed(myproc())) {
      release(&tickslock);
      return -1;
    }
    sleep_prepare(&ticks);
    release(&tickslock);
    sleep();
    acquire(&tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kkill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}





