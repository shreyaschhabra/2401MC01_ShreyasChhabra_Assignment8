#include "types.h"
#include "stat.h"
#include "user.h"

static void
show(char *label)
{
  struct meminfo mi;

  if(getmeminfo(&mi) < 0){
    printf(2, "memtest: getmeminfo failed\n");
    exit();
  }
  printf(1, "%s: total=%d free=%d process=%d page-tables=%d\n",
         label, mi.total_pages, mi.free_pages, mi.process_pages,
         mi.pagetable_pages);
}

int
main(void)
{
  char *p;
  int i, pid;

  show("before allocation");
  p = sbrk(4 * 4096);
  if(p == (char*)-1){
    printf(2, "memtest: sbrk failed\n");
    exit();
  }
  for(i = 0; i < 4; i++)
    p[i * 4096] = i;
  show("after allocation");

  pid = fork();
  if(pid < 0){
    printf(2, "memtest: fork failed\n");
    exit();
  }
  if(pid == 0){
    show("child");
    exit();
  }
  sleep(10);
  show("parent while child exists");
  wait();
  show("parent after child reaped");
  exit();
}
