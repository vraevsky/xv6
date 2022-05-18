/* this is a place holder.
 * replace with your own code
 */

#include "types.h"
#include "user.h"

int test_waitpid(){
    // return 0 if success

    // 1) wait for non existing child
    // You do it!

    // 2) fork a child, then wait for it to terminate
    int child_pid = fork();
    if(child_pid == 0){
        // in child
        sleep(10);
        return 0;
    }else{
        // in parent
        int ret = -1; // <<<<<< waitpid(child_pid,0,0);
        if(ret == -1){
            printf(1,"error calling waitpid");
            return 1;
        } else return 0;
    }
}


int main(){
    printf(1,"hello from testwait\n");
    test_waitpid();
    exit();
}
