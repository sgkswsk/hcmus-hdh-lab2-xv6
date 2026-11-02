#include "kernel/types.h"
#include "user/user.h"
#include "kernel/sysinfo.h"

int main() {
	printf("executing SYSCALL sysinfo...\n");

	struct sysinfo si;
	uint64 code;
	if ((code = sysinfo(&si))) {
		printf("sysinfo: syscall failed(%lu)\n", code);
		exit(1);
	}

	printf("struct sysinfo {\n");
	printf("\t.freemem = %lu bytes\n", si.freemem * 4096);
	printf("\t.nproc = %d\n", si.nproc);
	printf("}\n");

	exit(0);
}
