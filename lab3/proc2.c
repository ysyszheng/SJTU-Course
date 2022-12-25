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
  FILE *fout = fopen("out.txt", "w");
  fd = open("fifo", O_RDONLY);
  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    fwrite(buf, 1, n, fout);
  }
  close(fd);
  fclose(fout);
  unlink("fifo");
}