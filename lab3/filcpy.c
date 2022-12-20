#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define BUFSIZE 1024

void syscpy(char *inName, char *outName) {
  int n;
  char buf[BUFSIZE];
  int fin = open(inName, O_RDONLY, S_IRUSR);
  int fout = open(outName, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR);
  // while ((n = read(fin, buf, 1)) > 0) {
  //   write(fout, buf, 1);
  // }
  while ((n = read(fin, buf, BUFSIZE)) > 0) {
    write(fout, buf, BUFSIZE);
  }
  close(fin);
  close(fout);
}

void filcpy(char *inName, char *outName) {
  FILE *fin = fopen(inName, "r");
  FILE *fout = fopen(outName, "w+");
  int n;
  char buf[BUFSIZE];
  // while ((n = fread(buf, 1, 1, fin)) > 0) {
  //   fwrite(buf, 1, 1, fout);
  // }
  while ((n = fread(buf, BUFSIZE, 1, fin)) > 0) {
    fwrite(buf, BUFSIZE, 1, fout);
  }
  fclose(fin);
  fclose(fout);
}

void ffcpy(char *inName, char *outName) {
  FILE *fin = fopen(inName, "r");
  FILE *fout = fopen(outName, "w");
  char ch;
  while ((fscanf(fin, "%c", &ch) != EOF)) {
    fprintf(fout, "%c", ch);
  }
  fclose(fin);
  fclose(fout);
}

void fccpy(char *inName, char *outName) {
  FILE *fin = fopen(inName, "r");
  FILE *fout = fopen(outName, "w");
  int ch;
  while ((ch = fgetc(fin)) != EOF) {
    fputc(ch, fout);
  }
  fclose(fin);
  fclose(fout);
}

void fscpy(char *inName, char *outName) {
  FILE *fin = fopen(inName, "r");
  FILE *fout = fopen(outName, "w");
  char buf[BUFSIZE];
  char *retstring;
  while ((retstring = fgets(buf, BUFSIZE, fin)) != NULL) {
    fputs(retstring, fout);
  }
  fclose(fin);
  fclose(fout);
}

int main() {
  char *fin = "in.txt";
  char *fout = "out.txt";
  clock_t begin, end;
  double time_spent;

  // printf("一次读写一个字节:\n");
  printf("一次读写1024字节:\n");

  begin = clock();
  syscpy(fin, fout);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("文件的系统调用\t%fs\n", time_spent);

  begin = clock();
  filcpy(fin, fout);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("文件的库函数\t%fs\n", time_spent);

  // ffcpy(fin,fout);
  // fccpy(fin,fout);
  // fscpy(fin,fout);
}