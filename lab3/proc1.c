#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd, n, nn;
  char buf[1024];
  FILE *fin = fopen("in.txt", "r");
  if (access("fifo", F_OK) == -1) {
    if (mknod("fifo", S_IFIFO | 0666, 0) < 0 && (errno != EEXIST)) {
      printf("nooo");
    }
    // printf("create, %d\n", nn);
  }
  fd = open("fifo", O_WRONLY);
  while ((n = fread(buf, 1, sizeof(buf), fin)) > 0) {
    nn = write(fd, buf, n);
    // printf("WRITE FIFO:\n%s\n", buf);
    // printf("%d\t%d\n", fd, nn);
  }
  close(fd);
  fclose(fin);
}