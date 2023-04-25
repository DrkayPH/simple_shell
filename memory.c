#include "kc_shell.h"

/**
 * my_bfree - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int my_bfree(void **ptr)
{
    if (ptr == NULL || *ptr == NULL) {
        return 0; // nothing to free
    }

    free(*ptr);
    *ptr = NULL;
    return 1;
}

