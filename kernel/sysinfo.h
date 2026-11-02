#ifndef SYSINFO_H
#define SYSINFO_H

#include "types.h"

struct sysinfo {
	uint64 freemem;
	int nproc;
};

#endif
