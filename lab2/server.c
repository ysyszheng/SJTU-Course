#include "utils.h"

int main() {
  struct msgtype buf;
  pid_t qid;
  FILE *fout = fopen("out.txt", "w+");
  if (fout == NULL) {
    perror("fopen");
    return -1;
  }

  if ((qid = msgget(MSGKEY, IPC_CREAT | 0666)) == -1) {
    return -1;
  }

  while (1) {
    msgrcv(qid, &buf, BUFFER_SIZE, MSGTYPE, MSG_NOERROR);

    if (buf.msize == 0) {
      break;
    }

    fputs(buf.mtext, fout);
    printf(ANSI_COLOR_GREEN
           "Server: " ANSI_COLOR_RESET
           "Received a message from a process\nmpid: " ANSI_COLOR_BLUE
           "%d" ANSI_COLOR_RESET ", mtext: " ANSI_COLOR_BLUE
           "%s" ANSI_COLOR_RESET,
           buf.mpid, buf.mtext);

    buf.mtype = buf.mpid;
    msgsnd(qid, &buf, sizeof(buf.mtext), 0);
    printf(ANSI_COLOR_GREEN
           "Server: " ANSI_COLOR_RESET
           "Send a message to a process, mpid: " ANSI_COLOR_BLUE
           "%d" ANSI_COLOR_RESET "\n",
           buf.mpid);
  }

  fclose(fout);
  return 0;
}