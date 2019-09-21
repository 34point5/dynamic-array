#include <stdio.h>
#include <time.h>

#include "DynamicString.h"

int main(int const argc, char const *argv[])
{
	printf("executing:\n");
	printf("\t");
	for(int i = 0; i < argc; ++i)
	{
		printf("%s ", argv[i]);
	}
	printf("\n\n");
	dyn_str_t s = dyn_str_init("01238w7nty4weuifjposlkxz,234567");
	dyn_str_show(s);

	dyn_str_extend(s, "boobs");
	dyn_str_show(s);
}

