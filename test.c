#include <dirent.h>
#include <stdio.h>
#include <sys/param.h>
#include <time.h>

#include "DynamicString.h"

void f1(void)
{
	printf("f1\n");
	return;
}
void f2(void)
{
	printf("f2\n");
	return;
}
void f3(void)
{
	printf("f3\n");
	return;
}



int main(int const argc, char const *argv[])
{
	printf("executing:\n");
	printf("\t");
	for(int i = 0; i < argc; ++i)
	{
		printf("%s ", argv[i]);
	}
	printf("\n\n");

	dyn_str_t s = dyn_str_init("ntreiuj");
	dyn_str_show(s);

	dyn_str_extend(s, "b");
	dyn_str_show(s);

	dyn_str_extend(s, "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt");
	dyn_str_show(s);

	dyn_str_delete(s);
	dyn_str_show(s);

	clock_t start, stop;
	start = clock();
	FILE *fptr = fopen(argv[1], "r");
	s = dyn_str_read(fptr, 183936241);
	if(s != NULL)
	{
		char *ptr = dyn_str_find(s, "is");
	}
	fclose(fptr);
	stop = clock();
	printf("%lf\n", (double)(stop - start) / CLOCKS_PER_SEC);
	// printf("%p\n\n", ptr);

	typedef void (*f)(void);
	f func[3] = {&f1, &f2, &f3};
	char *error_strings[] = {"water", "smoke", "fire"};
	for(int i = 0; i < 3; ++i)
	{
		printf("%s\t", error_strings[i]);
		func[i]();
	}
}

