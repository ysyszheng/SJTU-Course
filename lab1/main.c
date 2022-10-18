#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


struct map {
  unsigned m_size;
  char *m_addr;
  struct map *next, *prior;
};
struct map *coremap;

char *lmalloc(unsigned size);

void lfree(unsigned size, char *addr);

char *lmalloc(unsigned size) { return NULL; }

void lfree(unsigned size, char *addr) { return; }

int main() {}