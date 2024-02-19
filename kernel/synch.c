#include "synch.h"

#define DEF_SEM_MAX 8

static int32_t sSemMax;
static int32_t sSem;

void Kernel_sem_init(int32_t max)
{
	sSemMax = (max <= 0) ? DEF_SEM_MAX : max;
	sSem = sSemMax;
}

bool Kernel_sem_test()
{
	if (sSem <= 0)
		return false;

	sSem--;

	return true;
}

void Kernel_sem_release()
{
	if (sSem >= sSemMax)
		sSem = sSemMax;

	sSem++;
}

