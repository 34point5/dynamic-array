#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////

// dynamic array structure
typedef struct
{
	dyn_arr_type *array; // where the elements are actually stored
	size_t capacity;     // maximum number of elements allowed
	size_t length;       // number of elements currently stored
}
Array;

///////////////////////////////////////////////////////////////////////////////

// construct dynamic array
_Bool dyn_arr_initialize(Array *a, size_t size, _Bool clear)
{
	// input sanity check
	if(size < 0)
	{
		size = 0;
	}
	a->length = size;

	// try to allocate space for array
	// keep some space to allow the array to grow
	size = size + 1 << 1;
	if(clear)
	{
		a->array = calloc(size, sizeof *a->array);
	}
	else
	{
		a->array = malloc(size * sizeof *a->array);
	}
	if(a->array == NULL)
	{
		printf("Failed to initialise dynamic array!\n");
		return 0;
	}
	a->capacity = size;

	return 1;
}

///////////////////////////////////////////////////////////////////////////////

// append an element to the end of the array
_Bool dyn_arr_append(Array *a, dyn_arr_type element)
{
	// check whether the array is full
	if(a->length == a->capacity)
	{
		// double the array capacity
		a->capacity <<= 1;

		// create temporary pointer in case reallocation fails
		dyn_arr_type *temp;
		temp = realloc(a->array, a->capacity * sizeof *temp);
		if(temp == NULL)
		{
			printf("Failed to append to dynamic array!\n");
			return 0;
		}
		a->array = temp;
	}

	// append the element
	// also increase the element counter
	a->array[a->length++] = element;

	return 1;
}

///////////////////////////////////////////////////////////////////////////////

// delete the dynamic array
void dyn_arr_delete(Array *a, _Bool clear)
{
	// erase the contents of the array if required
	if(clear)
	{
		memset(a->array, 0, a->capacity);
	}

	// release memory used by the array as well as the structure
	free(a->array);
}

///////////////////////////////////////////////////////////////////////////////

// pop the last element in the array
dyn_arr_type dyn_arr_pop(Array *a, _Bool clear)
{
	// cannot pop an empty array
	if(a->length == 0)
	{
		printf("Cannot pop an empty dynamic array!\n");
		return 0;
	}

	// decrement the array length
	// but do not decrease the capacity of the array
	dyn_arr_type popped_element;
	popped_element = a->array[--a->length];

	// erase the element if required
	if(clear)
	{
		a->array[a->length] = 0;
	}

	return popped_element;
}

