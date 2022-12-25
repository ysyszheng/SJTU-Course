#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char *inName = "in.txt";
  char *outName = "out.txt";
  int chan[2];
  char buf[1024];
  int n;
  pipe(chan);

  if (fork()) {
    close(chan[0]);
    FILE *fin = fopen(inName, "r");
    while ((n = fread(buf, 1, sizeof(buf), fin)) > 0) {
      write(chan[1], buf, n);
    }
    close(chan[1]);
    fclose(fin);
  } else {
    close(chan[1]);
    FILE *fout = fopen(outName, "w");
    while ((n = read(chan[0], buf, sizeof(buf)))) {
      fwrite(buf, 1, n, fout);
    }
    close(chan[0]);
    fclose(fout);
  }
}