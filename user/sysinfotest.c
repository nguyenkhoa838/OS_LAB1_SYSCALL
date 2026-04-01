#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct sysinfo info;

  if (sysinfo(&info) < 0) {
    printf("sysinfo failed\n");
    exit(1);
  }

  printf("sysinfo:\n");
  printf("  free memory:  %lu bytes\n", info.freemem);
  printf("  processes:    %lu\n", info.nproc);
  printf("  open files:   %lu\n", info.nopenfiles);

  exit(0);
}
