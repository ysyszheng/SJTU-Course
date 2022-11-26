#include "utils.h"

extern int creatsem();
extern void P(), V();

static int flag = 1;

void func() { flag = 0; }

int main() {
  time_t t;
  srand((unsigned)time(&t));

  FILE *fin = fopen("in.txt", "r+");
  FILE *fout = fopen("out.txt", "w+");
  char *segaddr;
  int segid, sid1, sid2;
  pid_t pid;
  int status;
  if ((segid = shmget(SHMKEY, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
    perror("shmget");
  }

  segaddr = shmat(segid, 0, 0);
  sid1 = creatsem(SEMKEY1);
  sid2 = creatsem(SEMKEY2);
  P(sid2);

  signal(SIGUSR1, func);

  if (!(pid = fork())) {
    while (1) {
      P(sid2);
      if (flag) {
        fputs(segaddr, fout);
        printf(ANSI_COLOR_GREEN "Child" ANSI_COLOR_RESET
                                " Received a message: %s",
               segaddr);
        V(sid1);
      } else {
        fclose(fout);
        V(sid1);
        break;
      }
    }
  } else {
    while (1) {
      P(sid1);
      if (fgets(segaddr, BUFFER_SIZE, fin)) {
        printf(ANSI_COLOR_GREEN "Parent" ANSI_COLOR_RESET " Send a message: %s",
               segaddr);
        V(sid2);
      } else {
        fclose(fin);
        V(sid2);
        kill(pid, SIGUSR1);
        wait(&status);
        break;
      }
    }
  }

  return 0;
}