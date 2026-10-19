#include "types.h"
#include "stat.h"
#include "user.h"

#define PGSIZE 4096
#define REGION (32 * 1024 * 1024)

static void
show(char *label)
{
  struct meminfo mi;

  if(getmeminfo(&mi) < 0){
    printf(2, "lazytest: getmeminfo failed\n");
    exit();
  }
  printf(1, "%s: free=%d process=%d page-tables=%d\n", label,
         mi.free_pages, mi.process_pages, mi.pagetable_pages);
}

int
main(void)
{
  char *base, ch = 'L';
  int fds[2], pid;

  show("before sbrk");
  base = sbrk(REGION);
  if(base == (char*)-1){
    printf(2, "lazytest: large sbrk failed\n");
    exit();
  }
  show("after sbrk without touches");

  base[0] = 1;
  base[8 * 1024 * 1024] = 2;
  base[16 * 1024 * 1024] = 3;
  base[24 * 1024 * 1024] = 4;
  base[REGION - 1] = 5;
  show("after five page touches");

  // read() must be able to populate a valid but untouched lazy page.
  if(pipe(fds) < 0 || write(fds[1], &ch, 1) != 1 ||
     read(fds[0], base + PGSIZE, 1) != 1){
    printf(2, "lazytest: syscall buffer test failed\n");
    exit();
  }
  close(fds[0]);
  close(fds[1]);
  show("after read into untouched page");

  pid = fork();
  if(pid < 0){
    printf(2, "lazytest: fork failed\n");
    exit();
  }
  if(pid == 0){
    base[12 * 1024 * 1024] = 6;
    show("child after new touch");
    exit();
  }
  wait();
  show("parent after child exit");

  pid = fork();
  if(pid < 0){
    printf(2, "lazytest: invalid-access fork failed\n");
    exit();
  }
  if(pid == 0){
    base[REGION + PGSIZE] = 7; // Beyond sz: only this child must die.
    printf(2, "lazytest: invalid access unexpectedly survived\n");
    exit();
  }
  wait();
  printf(1, "parent survived child's invalid access\n");
  exit();
}
