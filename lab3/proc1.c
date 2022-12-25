#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd, n;
  char buf[1024];
  FILE *fin = fopen("in.txt", "r");
  mknod("fifo", S_IFIFO | 0666, 0);
  fd = open("fifo", O_WRONLY);
  while ((n = fread(buf, 1, sizeof(buf), fin)) > 0) {
    write(fd, buf, n);
  }
  close(fd);
  fclose(fin);
}