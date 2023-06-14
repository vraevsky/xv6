#include "types.h"
#include "stat.h"
#include "user.h"
#include "proc_user_helper.h"
#include "proc_user.h"
#include <stddef.h>

void
call_lsprox()
{
    lsprox();
}

int
main(int argc, char *argv[])
{
  call_lsprox();
  exit();
}
