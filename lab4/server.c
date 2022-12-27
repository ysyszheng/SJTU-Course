#include "sockcom.h"

int main() {
  int newsockfd, sockfd, length, count;
  struct sockaddr_in server;
  char buf[1024];
  FILE *frecv;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("[ERROR]:\tsocket\n");
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 6666;
  server.sin_port = htons(server.sin_port);

  if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("[ERROR]:\tbind\n");
  }

  length = sizeof(server);
  if (getsockname(sockfd, (struct sockaddr *)&server, &length) < 0) {
    printf("[ERROR]:\tgetsockname\n");
  }

  listen(sockfd, 5);

  while (1) {
    newsockfd = accept(sockfd, (struct sockaddr *)0, (int *)0);
    printf("[INFO]:\tconnect success\n");

    if (!fork()) {
      close(sockfd);
      bzero(buf, sizeof(buf));
      if ((count = recv(sockfd, buf, sizeof(buf), 0)) < 0) {
        printf("[ERROR]:\tread\n");
      }

      frecv = fopen("out.txt", "w");
      fwrite(buf, 1, count, frecv);
      printf("[INFO]:\twrite %d bytes\n", count);
      fclose(frecv);
    }
    close(newsockfd);
  }
}