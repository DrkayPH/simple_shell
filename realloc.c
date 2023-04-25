#include "kc_shell.h"

/**
 * free_array - frees an array of pointers
 * @arr: array of pointers to be freed
 * @len: length of the array
 */
void free_array(void **arr, size_t len)
{
    if (arr == NULL)
        return;

    for (size_t i = 0; i < len; i++) {
        if (arr[i] != NULL) {
            free(arr[i]);
            arr[i] = NULL;
        }
    }

    free(arr);
    arr = NULL;
}

/**
 * _strncpy - copies a string up to n bytes
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 * @n: maximum number of bytes to copy
 *
 * Return: pointer to the destination string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';

	return dest;
}


/**
 * _my_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *_my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *new_ptr;

    if (!ptr)
        return malloc(new_size);

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    if (new_size <= old_size)
        return ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    memcpy(new_ptr, ptr, old_size);
    free(ptr);

    return new_ptr;
}

