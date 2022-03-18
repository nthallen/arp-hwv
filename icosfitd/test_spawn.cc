#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define ICOSsum_FIFO_PATH "ICOSsum.fifo"
#define PTE_FIFO_PATH "PTE.fifo"

void cleanup_fifo(const char *path) {
  if (unlink(path) != 0) {
    if (errno != ENOENT) {
      fprintf(stderr, "Error %d from unlink(%s): %s\n",
        errno, path, strerror(errno));
      exit(1);
    }
  }
}

void setup_fifo(const char *path) {
  cleanup_fifo(path);
  if (mkfifo(path, 0664) == -1) {
    fprintf(stderr, "Error %d creating fifo %s: %s",
      errno, path, strerror(errno));
    exit(1);
  }
}

int main(int argc, char **argv) {
  setup_fifo(PTE_FIFO_PATH);
  setup_fifo(ICOSsum_FIFO_PATH);
  int PTEfd = open(PTE_FIFO_PATH, O_WRONLY|O_NONBLOCK);
  while (PTEfd < 0) {
    // This demonstrates that we cannot open a FIFO
    // for write until someone has opened it for read.
    fprintf(stderr, "Error %d opening fifo %s: %s\n",
      errno, PTE_FIFO_PATH, strerror(errno));
    sleep(3);
    PTEfd = open(PTE_FIFO_PATH, O_WRONLY|O_NONBLOCK);
  }
  printf("Opened PTEfd\n");
  int SUMfd = open(ICOSsum_FIFO_PATH, O_RDONLY|O_NONBLOCK);
  printf("Opened SUMfd\n");
  FILE *LOGfp = fopen("ICOSsum.log", "a");
  if (PTEfd < 0 || SUMfd < 0 || LOGfp == 0) {
    fprintf(stderr, "Unable to open one of the files\n");
    exit(1);
  }
  // posix_spawn("icosfit", icosfit_file);
  cleanup_fifo(PTE_FIFO_PATH);
  cleanup_fifo(ICOSsum_FIFO_PATH);
  return 0;
}
