#include "utils.h"

void func() { printf("Aha! I am alive!\n"); }

int main() {
  int status;
  pid_t pid;
  signal(SIGUSR1, func);

  if ((pid = fork())) {
    /* parent process */
    FILE *f1 = fopen("file1.txt", "w");
    FILE *f2 = fopen("file2.txt", "w");
    if (f1 == NULL) {
      printf("Error opening file1.txt!\n");
      exit(1);
    }
    if (f2 == NULL) {
      printf("Error opening file2.txt!\n");
      exit(1);
    }

    const char *text1 = "I love SJTU!";
    const char *text2 = "I love Operation Systems!";
    fprintf(f1, "Text1: %s\n", text1);
    fprintf(f2, "Text2: %s\n", text2);
    fclose(f1);
    fclose(f2);

    printf(ANSI_COLOR_GREEN "Parent: " ANSI_COLOR_RESET "Signal send.\n");
    kill(pid, SIGUSR1);

    wait(&status);
    printf(ANSI_COLOR_GREEN "Parent: " ANSI_COLOR_RESET
                            "Process finished, status = %d\n",
           status);

  } else {
    /* child process */
    sleep(10);
    printf(ANSI_COLOR_GREEN "Child: " ANSI_COLOR_RESET "Signal received.\n");
    execl("/bin/cat", "cat", "./file1.txt", "./file2.txt", (char *)0);
    printf(ANSI_COLOR_RED "execl error!\n" ANSI_COLOR_RESET);
    exit(2);
  }
}