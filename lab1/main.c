/*
 * Yusen Zheng
 * 2022-10-19
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"

#define CORE_SIZE 1000
#define VERBOSE 1

struct map {
  unsigned m_size;
  char *m_addr;
  struct map *next, *prior;
};
// Lookup pointer to the starting position
struct map *coremap;

// function declarations
void init_coremap(unsigned);
char *lmalloc(unsigned);
void lfree(unsigned, char *);
void print_free_mem();

// function definitions
void init_coremap(unsigned size) {
  coremap = (struct map *)malloc(sizeof(struct map));
  coremap->m_size = size;
  coremap->m_addr = (char *)malloc(size);
  coremap->next = coremap;
  coremap->prior = coremap;
  printf("Simulation kernel space allocation succeeded!\n");
  printf("kernel address: %p - %p, space "
         "size: %u\n",
         coremap->m_addr, coremap->m_addr + size, size);
}

char *lmalloc(unsigned size) {
  // all memory has been allocated
  if (coremap == NULL) {
    printf(ANSI_COLOR_RED "****** ERROR: All kernel space has been used! "
                          "******" ANSI_COLOR_RED "\n");
    return NULL;
  }

  char *addr;
  struct map *p, *q;
  p = q = coremap; //  p move, q fix

  do {
    // current free partition size is appropriate
    if (p->m_size >= size) {
      addr = p->m_addr;
      p->m_addr += size;

      // the entire partition is allocated
      if ((p->m_size -= size) == 0) {
        // all memory has been allocated
        if (p->next == p) {
          printf(ANSI_COLOR_YELLOW "****** WARNING: All kernel space has been "
                                   "used! ******" ANSI_COLOR_YELLOW "\n");
          coremap = NULL;
        } else {
          coremap = p->next;
          p->next->prior = p->prior;
          p->prior->next = p->next;
        }
        free(p);
      }

      printf(ANSI_COLOR_GREEN "Memory allocated succeeded, address: %p - %p, "
                              "size: %u" ANSI_COLOR_GREEN "\n",
             addr, addr + size, size);
      if (VERBOSE) {
        print_free_mem();
      }
      return addr;
    } else {
      p = p->next;
    }
  } while (p != q);

  printf(ANSI_COLOR_RED "****** ERROR: Required memory space [%d byte] is too "
                        "large! ******" ANSI_COLOR_RED "\n",
         size);
  return NULL;
}

void lfree(unsigned size, char *addr) {
  if (addr == NULL) {
    printf(ANSI_COLOR_RED
           "****** ERROR: Memory address is NULL! ******" ANSI_COLOR_RED "\n");
  }

  // all memory has been allocated
  if (coremap == NULL) {
    coremap = (struct map *)malloc(sizeof(struct map));
    coremap->m_addr = addr;
    coremap->m_size = size;
    coremap->prior = coremap;
    coremap->next = coremap;
    return;
  }

  // find the right address, let addr between p->m_addr & p->next->m_addr
  struct map *p = coremap; // TODO after free, need to change coremap position
  while ((p->m_addr < addr &&
          p->next->m_addr > addr) ||       // e.g. .. 100 .. [250] .. 300 ..
         ((p->m_addr < addr ||             // e.g. [50] .. 100 ..
           p->next->m_addr > addr) &&      // e.g. .. 800 [900]
          p->m_addr >= p->next->m_addr)) { // = for only one node
    p = p->next;
  }

  if (p->m_addr + p->m_size == addr) {
    if (p->next->m_addr == addr + size) { // case 1: adjacent to front and rear
      p->m_size += (size + p->next->m_size);
      struct map *q = p->next;
      p->next = q->next;
      p->next->prior = p;
      free(q);
    } else { // case 2: adjacent to front
      p->m_size += size;
    }
  } else {
    if (p->next->m_addr == addr + size) { // case 3: adjacent to rear
      p->next->m_addr -= size;
      p->next->m_size += size;
    } else { // case 4: not adjacent
      struct map *newCoremap = (struct map *)malloc(sizeof(struct map));
      newCoremap->m_addr = addr;
      newCoremap->m_size = size;
      newCoremap->next = p->next;
      newCoremap->prior = p;
      p->next->prior = newCoremap;
      p->next = newCoremap;
    }
  }

  printf(ANSI_COLOR_GREEN
         "Memory free succeeded, address: %p - %p, size: %u" ANSI_COLOR_GREEN
         "\n",
         addr, addr + size, size);
  if (VERBOSE) {
    print_free_mem();
  }
  return;
}

// print free memory partition
void print_free_mem() {
  printf(ANSI_COLOR_BLUE
         "****************Start Print****************" ANSI_COLOR_BLUE "\n");
  struct map *p = coremap;
  printf("Avaliable memory partition:\n");
  do {
    printf("memory address: %p - %p, size: %u\n", p->m_addr,
           p->m_addr + p->m_size, p->m_size);
  } while (p != coremap);
  printf(ANSI_COLOR_BLUE
         "****************End Print****************" ANSI_COLOR_BLUE "\n");
  return;
}

int main() {
  init_coremap(CORE_SIZE);

  // printf("%p\t%p\t%p\t%d\n", coremap, coremap->m_addr,
  //        coremap->m_addr + coremap->m_size, coremap->m_size);

  char *p1 = lmalloc(200);
  char *p2 = lmalloc(350);
  lfree(100, p1);
  char *p3 = lmalloc(100);
  lfree(350, p2);
  char *p4 = lmalloc(400);
  lfree(100, p3);
  lfree(400, p4);
  print_free_mem();

  return 0;
}