typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;

// Physical-memory statistics returned by getmeminfo().
struct meminfo {
  uint total_pages;
  uint free_pages;
  uint process_pages;
  uint pagetable_pages;
};
