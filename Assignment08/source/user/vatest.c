#include "types.h"
#include "stat.h"
#include "user.h"

int global_value = 8;

int
main(void)
{
  int local_value = 16;
  int *heap_value;
  int pid;

  heap_value = malloc(sizeof(*heap_value));
  if(heap_value == 0){
    printf(2, "vatest: malloc failed\n");
    exit();
  }
  *heap_value = 32;
  printf(1, "global: VA 0x%x PA 0x%x\n", &global_value,
         va2pa((int)&global_value));
  printf(1, "local:  VA 0x%x PA 0x%x\n", &local_value,
         va2pa((int)&local_value));
  printf(1, "malloc: VA 0x%x PA 0x%x\n", heap_value,
         va2pa((int)heap_value));
  printf(1, "unmapped 0x7fffffff: %d\n", va2pa(0x7fffffff));

  pid = fork();
  if(pid < 0){
    printf(2, "vatest: fork failed\n");
    exit();
  }
  if(pid == 0){
    printf(1, "child: global VA 0x%x PA 0x%x\n", &global_value,
           va2pa((int)&global_value));
    exit();
  }
  printf(1, "parent: global VA 0x%x PA 0x%x\n", &global_value,
         va2pa((int)&global_value));
  wait();
  free(heap_value);
  exit();
}
