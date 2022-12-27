#include "sockcom.h"

int main() {
  int newsockfd, sockfd, length, count;
  struct sockaddr_in server;
  char buf[1024];
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  FILE *frecv;
  if (sockfd < 0) {
    perror("socket");
  }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 6666;
  server.sin_port = htons(server.sin_port);
  if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("bind");
  }
  length = sizeof(server);
  if (getsockname(sockfd, (struct sockaddr *)&server, &length) < 0) {
    perror("getsockname");
  }
  listen(sockfd, 5);
  while (1) {
    newsockfd = accept(sockfd, (struct sockaddr *)0, (int *)0);
    if (!fork()) {
      close(sockfd);
      bzero(buf, sizeof(buf));
      if ((count = recv(sockfd, buf, sizeof(buf), 0)) < 0) {
        perror("read");
      }
      frecv = fopen("out.txt", "w");
      fwrite(buf, 1, 1, frecv);
      fclose(frecv);
    }
    close(newsockfd);
  }
}