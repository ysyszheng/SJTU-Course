#include "sockcom.h"

int main(int argc, char **argv) {
  int sockfd, n;
  struct sockaddr_in server;
  struct hostent *hp, *gethostbyname();
  char msg[1024];
  // FILE *fsend = fopen("in", "rb");
  FILE *fsend = fopen("in.txt", "r");

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("[ERROR]:\tsocket\n");
    exit(1);
  }

  if ((hp = gethostbyname(argv[1])) == NULL) {
    printf("[ERROR]:\tUnknow hp %s\n", argv[1]);
    exit(1);
  }

  server.sin_family = AF_INET;
  bcopy((char *)hp->h_addr, (char *)&server.sin_addr.s_addr, hp->h_length);
  server.sin_port = htons(atoi(argv[2]));

  if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("[ERROR]:\tconnect\n");
    exit(1);
  }

  printf("[INFO]:\tconnect\n");

  bzero(msg, sizeof(msg));
  while ((n = fread(msg, 1, sizeof(msg), fsend)) > 0) {
    if ((send(sockfd, msg, n, 0)) < 0) {
      printf("[ERROR]:\tsend\n");
    }
    printf("[INFO]:\tclient send %d bytes\n", n);
    bzero(msg, sizeof(msg));
  }

  printf("[INFO]:\tEOF\n");
  close(sockfd);
  fclose(fsend);
  exit(0);
}