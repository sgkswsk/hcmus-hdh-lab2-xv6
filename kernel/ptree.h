#ifndef _PTREE_H_
#define _PTREE_H_

#include "types.h"

struct ptreeinfo {
  int pid;
  int ppid;
  int state;
  uint64 memsize;   // so byte bo nho user cua tien trinh
  char name[16];
};

#endif
