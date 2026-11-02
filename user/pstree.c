#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/ptree.h"
#include "user/user.h"

struct ptreeinfo procs[NPROC];
int visited[NPROC];
int nprocs = 0;

// Ham de quy in tien trinh theo cau truc cay cha - con
void
print_tree(int idx, int depth)
{
  visited[idx] = 1;

  // Thut le: moi cap con thut vao 2 dau cach so voi cha
  for(int i = 0; i < depth; i++) {
    printf("  ");
  }

  // In thong tin theo dung dinh dang mau trong de bai
  printf("%d %s state=%d mem=%lu\n",
         procs[idx].pid,
         procs[idx].name,
         procs[idx].state,
         procs[idx].memsize);

  // Tim va in de quy tat ca cac tien trinh con cua tien trinh hien tai
  for(int i = 0; i < nprocs; i++) {
    if(!visited[i] && procs[i].ppid == procs[idx].pid) {
      print_tree(i, depth + 1);
    }
  }
}

int
main(int argc, char *argv[])
{
  // Goi system call ptree
  nprocs = ptree(procs, NPROC);
  if(nprocs < 0) {
    fprintf(2, "pstree: ptree syscall failed\n");
    exit(1);
  }

  // Sap xep cac tien trinh theo pid tang dan
  for(int i = 0; i < nprocs - 1; i++) {
    for(int j = i + 1; j < nprocs; j++) {
      if(procs[i].pid > procs[j].pid) {
        struct ptreeinfo tmp = procs[i];
        procs[i] = procs[j];
        procs[j] = tmp;
      }
    }
  }

  for(int i = 0; i < nprocs; i++) {
    visited[i] = 0;
  }

  // Tim cac nut goc (tien trinh khong co cha trong danh sach hien tai, vi du: init)
  for(int i = 0; i < nprocs; i++) {
    int has_parent = 0;
    for(int j = 0; j < nprocs; j++) {
      if(i != j && procs[j].pid == procs[i].ppid) {
        has_parent = 1;
        break;
      }
    }
    if(!has_parent && !visited[i]) {
      print_tree(i, 0);
    }
  }

  // Phong truong hop con tien trinh nao chua duoc duyet
  for(int i = 0; i < nprocs; i++) {
    if(!visited[i]) {
      print_tree(i, 0);
    }
  }

  exit(0);
}