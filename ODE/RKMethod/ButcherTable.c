#include <stdlib.h>
#include "ButcherTable.h"

ButcherTable euler;

void InitializeButcherTable()
{
	euler = CreateERKButcherTable(1, 1);
	euler.c[0] = 0;
	euler.b[0] = 1;
}

ButcherTable GetButcherTable(RKMethodType type)
{
	ButcherTable dammy = {0, 0, 0, 0, 0, 0};
	switch(type)
	{
	case Euler:
		return euler;
	default:
		return dammy;
	}
}

void FinalizeButcherTable()
{
	DeleteERKButcherTable(&euler);
}

ButcherTable CreateERKButcherTable(uint64_t stage, uint64_t embed)
{
	ButcherTable b = {0, 0, 0, 0, 0, 0};
	b.stage = stage;
	b.embed = embed;
	b.buf = malloc(sizeof(double)*(b.stage + b.stage + b.stage*(b.stage - 1)/2) + sizeof(double*)*(b.stage - 1));
	b.a = (double**)((double*)b.buf + b.stage + b.stage + b.stage*(b.stage - 1)/2);
	b.c = b.buf;
	for(int i = 0; i < b.stage - 1; ++i)
		b.a[i] = b.c + b.stage + i*(i + 1)/2;
	b.b = b.buf + b.stage + b.stage*(b.stage - 1)/2;
	return b;
}

void DeleteERKButcherTable(ButcherTable *b)
{
	free(b->buf);
	b->stage = b->embed = 0;
	b->b = b->c = b->buf = 0;
	b->a = 0;
}
