#include <dirent.h>
#include <stdio.h>
#include <sys/param.h>
#include <time.h>

#include "DynamicString.h"

char *strrstr(const char *s, const char *m) {
    char *last = NULL;
    size_t n = strlen(m);

    while ((s = strchr(s, *m)) != NULL) {
        if (!strncmp(s, m, n))
            last = (char *)s;
        if (*s++ == '\0')
            break;
    }
    return last;
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

	dyn_str_t s = dyn_str_init("boo");
	dyn_str_show(s);

	dyn_str_extend(s, "b");
	dyn_str_show(s);

	dyn_str_extend(s, "ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttits");
	dyn_str_show(s);

	dyn_str_delete(s);
	dyn_str_show(s);

	clock_t start, stop;
	start = clock();
	FILE *fptr = fopen(argv[1], "r");
	s = dyn_str_read(fptr);
	char *ptr = dyn_str_rfind(s, "tits");
	// char *ptr = dyn_str_find(s, "tits");
	fclose(fptr);
	stop = clock();
	printf("%lf\n", (double)(stop - start) / CLOCKS_PER_SEC);
	// printf("%s\n", strstr(s->String, "boobsboobsboobstits"));
	// printf("%s\n", dyn_str_find(s, "boobsboobsboobstits"));

	printf("rfind\n");
	// char *ptr = dyn_str_rfind(s, "Nature....");
	if(ptr == NULL)
	{
		printf("not found\n");
	}
	else
	{
		printf("found: %s\n", ptr);
	}

	if(0 && strstr("abab", "ba"))
	{
		printf("substring\n");
		char a[2048];
		printf("%s\n", realpath(argv[1], a));
    DIR *d;

    struct dirent *dir;

    d = opendir(".");

    if (d)

    {

        while ((dir = readdir(d)) != NULL)

        {

            printf("%s\n", dir->d_name);

        }

        closedir(d);

    }
	}
}

