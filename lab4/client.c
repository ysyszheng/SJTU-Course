#include "sockcom.h"

int main(int argc, char **argv) {
  int sockfd;
  struct sockaddr_in server;
  struct hostent *hp, *gethostbyname();
  char msg[1024];
  FILE *fsend = fopen("in.txt", "r");
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Opening stream socket");
  }
  if ((hp = gethostbyname(argv[1])) == NULL) {
    fprintf(stderr, "%s: Unknow\n", argv[1]);
    exit(2);
  }
  server.sin_family = AF_INET;
  bcopy((char *)hp->h_addr, (char *)&server.sin_addr.s_addr, hp->h_length);
  server.sin_port = htons(atoi(argv[2]));
  if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("Connecting stream socket");
  }
  while ((fread(msg, 1, 1, fsend) > 0)) {
    if (send(sockfd, msg, strlen(msg), 0) < 0) {
      perror("Failed to send");
    }
    bzero(msg, sizeof(msg));
  }
  printf("EOF\n");
  close(sockfd);
  fclose(fsend);
  exit(0);
}