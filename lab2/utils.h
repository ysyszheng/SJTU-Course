#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MSGKEY 1234
#define MSGTYPE 1
#define BUFFER_SIZE 1024

struct msgtype {
  long mtype;
  int mpid;
  size_t msize;
  char mtext[BUFFER_SIZE];
};

#define SHM_SIZE 1024
#define SHMKEY rand()
#define SEMKEY1 rand() + 1
#define SEMKEY2 rand() + 2

int creatsem(key_t key) {
  int semid;
  union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
  } semopts;
  semid = semget(key, 1, IPC_CREAT | 0666);
  if (semid == -1) {
    perror("semget");
  }
  semopts.val = 1;
  if (semctl(semid, 0, SETVAL, semopts) == -1) {
    perror("semctl");
  }
  return semid;
}

static void semcall(int semid, int op) {
  struct sembuf semopbuf;
  semopbuf.sem_num = 0;
  semopbuf.sem_op = op;
  semopbuf.sem_flg = 0;
  if (semop(semid, &semopbuf, 1) == -1) {
    perror("semop");
  }
}

void P(int semid) { semcall(semid, -1); }
void V(int semid) { semcall(semid, 1); }

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

#endif // UTILS_H