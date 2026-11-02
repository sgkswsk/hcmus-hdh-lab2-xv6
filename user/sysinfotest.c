#include "user/user.h"
#include "kernel/types.h"
#include "kernel/sysinfo.h"

int main() {
	printf("executing SYSCALL sysinfo...\n");

	struct sysinfo si;
	if (!sysinfo(&si)) {
		printf("sysinfo: syscall failed\n");
		exit(1);
	}

	printf("struct sysinfo {\n");
	printf("\t.freemem = %ull\n", si.freemem * 4096);
	printf("\t.nproc = %ull\n", si.nproc);
	printf("}\n");

	exit(0);
}
