#include "sockcom.h"

int main() {
  int newsockfd, sockfd, length, count;
  struct sockaddr_in server;
  char buf[1024];
  FILE *frecv = fopen("out.txt", "w");

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("[ERROR]:\tsocket\n");
    exit(1);
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 6666;
  server.sin_port = htons(server.sin_port);

  if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
    printf("[ERROR]:\tbind\n");
    exit(1);
  }

  listen(sockfd, 5);
  printf("[INFO]:\tlisten\n");
  newsockfd = accept(sockfd, (struct sockaddr *)0, (int *)0);

  bzero(buf, sizeof(buf));
  while ((count = recv(newsockfd, buf, sizeof(buf), 0)) > 0) {
    fwrite(buf, 1, count, frecv);
    printf("[INFO]:\tserver write %d bytes\n", count);
    bzero(buf, sizeof(buf));
  }

  printf("[INFO]:\tEOF\n");

  close(sockfd);
  close(newsockfd);
  fclose(frecv);
}