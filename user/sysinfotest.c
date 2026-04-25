// #include "kernel/param.h"
// #include "kernel/types.h"
// #include "kernel/sysinfo.h"
// #include "user/user.h"

// int
// main(int argc, char *argv[])
// {
//   struct sysinfo info;

//   if (sysinfo(&info) < 0) {
//     printf("sysinfo failed\n");
//     exit(1);
//   }

//   printf("sysinfo:\n");
//   printf("  free memory:  %lu bytes\n", info.freemem);
//   printf("  processes:    %lu\n", info.nproc);
//   printf("  open files:   %lu\n", info.nopenfiles);

//   exit(0);
// }

#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct sysinfo info_start, info_after;
  int pid, fd;

  if (sysinfo(&info_start) < 0) {
    printf("sysinfo failed\n");
    exit(1);
  }
  printf("free memory: %lu bytes\n", info_start.freemem);
  printf("processes:   %lu\n", info_start.nproc);
  printf("open files:  %lu\n\n", info_start.nopenfiles);

  printf("Test nproc\n");
  pid = fork();
  if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }
  if(pid == 0){
    sysinfo(&info_after);
    printf("after fork: %lu \n\n", info_after.nproc);
    exit(0);
  }
  wait(0);

  printf("Test freemem\n");
  if((uint64)sbrk(4096) != 0xffffffffffffffff){
    sysinfo(&info_after);
    printf("after sbrk: %lu bytes\n\n", info_after.freemem);
  } else {
    printf("sbrk failed\n\n");
  }

  printf("Test nopenfiles\n");
  fd = open("README", 0); 
  if(fd >= 0) {
    sysinfo(&info_after);
    printf("after open: %lu\n", info_after.nopenfiles);

    close(fd);
    
    sysinfo(&info_after);
    printf("after close: %lu\n\n", info_after.nopenfiles);
  } else {
    printf("Failed to open README for test.\n\n");
  }

  printf("Test finished.\n");
  exit(0);
}