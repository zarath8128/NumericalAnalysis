#include <stdlib.h>
#include "ERKMethod.h"

ButcherTable bt = {0, 0, 0, 0, 0, 0};

void SetButcherTable(ButcherTable butcher)
{
	free(bt.buf);
}
