#include "utils.h"

int main() {
  struct msgtype buf;
  pid_t qid, pid;
  FILE *fin = fopen("in.txt", "r+");
  if (fin == NULL) {
    perror("fopen");
    exit(1);
  }
  qid = msgget(MSGKEY, IPC_CREAT | 0666);

  while (fgets(buf.mtext, BUFFER_SIZE, fin) > 0) {
    buf.mpid = pid = getpid();
    buf.mtype = MSGTYPE;
    buf.msize = strlen(buf.mtext);
    msgsnd(qid, &buf, sizeof(buf.mtext), 0);

    printf(ANSI_COLOR_GREEN "Client: " ANSI_COLOR_RESET
                            "Send a message to server\nmpid: " ANSI_COLOR_BLUE
                            "%d" ANSI_COLOR_RESET ", mtext: " ANSI_COLOR_BLUE
                            "%s" ANSI_COLOR_RESET,
           buf.mpid, buf.mtext);

    msgrcv(qid, &buf, BUFFER_SIZE, pid, MSG_NOERROR);
    printf(ANSI_COLOR_GREEN
           "Client: " ANSI_COLOR_RESET
           "Received a message from server, type: " ANSI_COLOR_BLUE
           "%ld" ANSI_COLOR_RESET "\n",
           buf.mtype);
  }

  buf.mpid = pid = getpid();
  buf.mtype = MSGTYPE;
  buf.msize = 0;
  msgsnd(qid, &buf, BUFFER_SIZE, 0);

  fclose(fin);
  return 0;
}