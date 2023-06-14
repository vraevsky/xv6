#include "types.h"
#include "stat.h"
#include "user.h"
#include "proc_user_helper.h"
#include "proc_user.h"
#include <stddef.h>

char buf[512];

static char *state[] = { "UNUSED", "EMBRYO", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE" };

void
call_lsproc()
{
    void *proc=NULL;
    proc=lsproc();
    int _state = ((struct proc_user *)proc)->state;
    printf(1, "%s %d; proc_name=%s\n",__func__,__LINE__,((struct proc_user *)proc)->name);
    printf(1, "%s %d; proc_pid=%d\n",__func__,__LINE__,((struct proc_user *)proc)->pid);
    printf(1, "%s %d; proc_state=%s\n",__func__,__LINE__,state[_state]);
    printf(1, "%s %d; proc_addr=0x%x\n",__func__,__LINE__,((struct proc_user *)proc)->self);
#if 0
    printf(1, "%s %d; proc_sz=0x%x\n",__func__,__LINE__,((struct proc_user *)proc)->sz);
    printf(1, "%s %d; proc_kstack=0x%x\n",__func__,__LINE__,((struct proc_user *)proc)->kstack);
#endif    
    printf(1, "%s %d; proc_parent=0x%x\n",__func__,__LINE__,((struct proc_user *)proc)->parent);
}

int
main(int argc, char *argv[])
{
  int i;

  for(i = 1; i < argc; i++){
      printf(1, "%s %d argument %s\n", __func__,__LINE__, argv[i]);
  }
  call_lsproc();
  exit();
}
