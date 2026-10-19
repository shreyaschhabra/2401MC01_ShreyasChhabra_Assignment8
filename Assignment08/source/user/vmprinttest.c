#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  char *heap;
  int i;

  printf(1, "vmprinttest: initial mappings\n");
  vmprint();

  heap = sbrk(8 * 4096);
  if(heap == (char*)-1){
    printf(2, "vmprinttest: sbrk failed\n");
    exit();
  }
  for(i = 0; i < 8; i++)
    heap[i * 4096] = i;
  printf(1, "vmprinttest: after growing and touching 8 pages\n");
  vmprint();

  if(sbrk(-4096) == (char*)-1){
    printf(2, "vmprinttest: shrink failed\n");
    exit();
  }
  printf(1, "vmprinttest: after shrinking 1 page\n");
  vmprint();
  exit();
}
