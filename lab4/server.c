#include "sockcom.h"
#include <stdio.h>
#include <sys/socket.h>

int main() {
  int sockfd, length, count;
  struct sockaddr_in server;
  char buf[1024];
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  FILE *frecv;
  if (sockfd < 0) {
    syserr("socket");
  }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0;
  if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    syserr("bind");
  }
  length = sizeof(server);
  if (getsockname(sockfd, (struct sockaddr *)&server, &length) < 0) {
    fatal("getsockname");
  }
  printf("socket port %d\n", server.sin_port);
  listen(sockfd, 5);
  while (1) {
    bzero(buf, sizeof(buf));
    if ((count = recv(sockfd, buf, sizeof(buf), 0)) < 0) {
      syserr("read");
    }
    frecv = fopen("out.txt", "w");
    fwrite(buf, 1, 1, frecv);
    fclose(frecv);
  }
  close(sockfd);
}