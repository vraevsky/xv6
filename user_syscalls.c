#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

static char *state[] = { "UNUSED", "EMBRYO", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE" };
void sys_lsprox(void) {
	int i;
    struct proc *cpu_proc;
	for ( i = 0 ; i < NCPU ; i++) {
        cpu_proc = cpus[i].proc;
        if ( cpu_proc == 0 )
            continue;
        cprintf("CPU [ %d ]:\n",i);
        cprintf("\tname\tpid\tstate\taddress\n",cpu_proc);
        while ( cpu_proc )  {
            cprintf("\t%s",cpu_proc->name);
            cprintf("\t%d",cpu_proc->pid);
            cprintf("\t%s",state[cpu_proc->state]);
            cprintf("\t%x\n",cpu_proc);
            cpu_proc=cpu_proc->parent;
        };
        cprintf("\n");
	}
}

#include "proc_user.h"
struct proc_user proc_user_data;
int sys_lsproc(void)
{
  int i;
  struct proc *curproc = myproc();
  uint sz=0, sp=0;
  pde_t *pgdir = curproc->pgdir;

  if((pgdir = setupkvm()) == 0)
    return -1;

  sz = PGROUNDUP(sz);
  if((sz = allocuvm(pgdir, sz, sz + 2*PGSIZE)) == 0)
    return -1;
  clearpteu(pgdir, (char*)(sz - 2*PGSIZE));
  sp = sz;

  proc_user_data.self = curproc;
  proc_user_data.sz = curproc->sz;
  proc_user_data.pgdir = curproc->pgdir;
  proc_user_data.state = curproc->state;
  proc_user_data.kstack = curproc->kstack;
  proc_user_data.pid = curproc->pid;
  proc_user_data.parent = curproc->parent;
  proc_user_data.tf = curproc->tf;
  proc_user_data.context = curproc->context;
  proc_user_data.chan = curproc->chan;
  proc_user_data.killed = curproc->killed;
  for ( i = 0 ; i < 16; i++) {
    proc_user_data.name[i]=curproc->name[i];
  }
  if(copyout(curproc->pgdir, sp, &proc_user_data, sizeof(proc_user_data)) < 0)
    return -1;
  return (int) sp;
}
