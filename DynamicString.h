#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE_RETURN_VALUE 0
#define SUCCESS_RETURN_VALUE 1

#define _FILE_OFFSET_BITS 64

///////////////////////////////////////////////////////////////////////////////

// dynamic string structure
typedef struct
{
	char   *String;  // address of the string
	size_t Length;   // current string length
	size_t Capacity; // maximum string length
}
*dyn_str_t;

///////////////////////////////////////////////////////////////////////////////

// calculate the nearest power of 2 greater than the input number
int nearest_power_of_2(size_t size)
{
	int power = 0;
	while(size)
	{
		size >>= 1;
		++power;
	}
	return power;
}

///////////////////////////////////////////////////////////////////////////////

// create a dynamic string
// initialise it according to the provided string
dyn_str_t dyn_str_init(char *s)
{
	// allocate memory for struct
	dyn_str_t dyn_str = malloc(sizeof *dyn_str);
	if(dyn_str == NULL)
	{
		printf("Failed to initialise dynamic string.\n");
		return NULL;
	}

	// calculate least power of 2 which is greater than length of string
	size_t s_length = strlen(s);
	int power = nearest_power_of_2(s_length);

	// set attributes of struct
	// 'Capacity' shall always be greater than 'Length'
	// because an extra slot is required for '\0'
	dyn_str->Capacity = (size_t)1 << power;
	dyn_str->Length = s_length;
	dyn_str->String = malloc(dyn_str->Capacity
	                         * sizeof *(dyn_str->String));
	memcpy(dyn_str->String, s, s_length + 1);

	return dyn_str;
}

///////////////////////////////////////////////////////////////////////////////

// show all attributes
void dyn_str_show(dyn_str_t dyn_str)
{
	printf("String:   %s\n", dyn_str->String);
	printf("Length:   %zd\n", dyn_str->Length);
	printf("Capacity: %zd\n\n", dyn_str->Capacity);
	return;
}

///////////////////////////////////////////////////////////////////////////////

// string pointer getter
char *dyn_str_get(dyn_str_t dyn_str)
{
	return dyn_str->String;
}

///////////////////////////////////////////////////////////////////////////////

// string length getter
size_t dyn_str_len(dyn_str_t dyn_str)
{
	return dyn_str->Length;
}

///////////////////////////////////////////////////////////////////////////////

// extend dynamic string
_Bool dyn_str_extend(dyn_str_t dyn_str, char *s)
{
	// calculate the size of the resultant string required
	size_t s_length = strlen(s);
	size_t required = dyn_str->Length + s_length + 1;

	// check whether the capacity is enough
	if(required > dyn_str->Capacity)
	{
		// capacity is not enough
		// keep doubling the capacity until it is enough
		while(required > dyn_str->Capacity)
		{
			dyn_str->Capacity <<= 1;
		}

		// allocate the above-calculated amount of space
		char *temp = realloc(dyn_str->String,
		                     dyn_str->Capacity * sizeof *temp);
		if(temp == NULL)
		{
			printf("Failed to extend dynamic string.\n");
			return FAILURE_RETURN_VALUE;
		}
		dyn_str->String = temp;
	}

	// now there is enough space to extend the string
	// append the second string to the first
	// jump to the null byte position of first string
	// then copy the second string from there
	char *ptr = dyn_str->String + dyn_str->Length;
	memcpy(ptr, s, s_length + 1);
	dyn_str->Length = required - 1;

	return SUCCESS_RETURN_VALUE;
}

///////////////////////////////////////////////////////////////////////////////

// delete dynamic string
void dyn_str_delete(dyn_str_t dyn_str)
{
	free(dyn_str->String);
	free(dyn_str);
	return;
}

///////////////////////////////////////////////////////////////////////////////

// read contents of a file into a string
dyn_str_t dyn_str_read(FILE *fptr, off_t maximum_size)
{
	// determine the size of the file
	fseek(fptr, 0, SEEK_END);
	off_t size = ftello(fptr);

	// if the file size exceeds the limit specified, don't read the file
	// low-memory systems will get a chance to prevent a freeze
	if(maximum_size != 0 && size > maximum_size)
	{
		return NULL;
	}

	// allocate space for dynamic string
	// there should enough space to store the file contents as a string
	// thus, calculate 'Capacity' like it is done in 'dyn_str_init'
	// however, 'Length' shall be initialised to zero
	// because text from the file is yet to be added to the string
	dyn_str_t dyn_str = malloc(sizeof *dyn_str);
	int power = nearest_power_of_2(size);
	dyn_str->Capacity = (size_t)1 << power;
	dyn_str->Length = size;
	dyn_str->String = malloc(dyn_str->Capacity
	                         * sizeof *(dyn_str->String));
	
	// read the entire file into memory
	fread(dyn_str->String, 1, size, fptr);
	dyn_str->String[size] = '\0';

	return dyn_str;
}

///////////////////////////////////////////////////////////////////////////////

// locate the first occurrence of a substring in a string
char *dyn_str_find(dyn_str_t dyn_str, char *s)
{
	return strstr(dyn_str->String, s);
}

///////////////////////////////////////////////////////////////////////////////

// locate the last occurrence of a substring in a string
// there is no 'strrstr' in the standard library
// also, 'strrchr' scans from the beginning of a string
// hence, this function is implemented from scratch
char *dyn_str_rfind(dyn_str_t dyn_str, char *s)
{
	// jump to the end of the string
	// this is where the substring search will start
	size_t s_length = strlen(s);
	char *position = dyn_str->String + dyn_str->Length - s_length;

	// keep decrementing the pointer
	// when first character match is found, compare the whole string
	// when pointer crosses the start of the main string, stop
	while(position >= dyn_str->String)
	{
		if(*position == *s && !strncmp(position, s, s_length))
		{
			return position;
		}
		--position;
	}

	return NULL;
}

