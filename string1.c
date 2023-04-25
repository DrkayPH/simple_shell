#include "kc_shell.h"

/**
 * my_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *my_strcpy(char *dest, const char *src)
{
    char *dest_ptr = dest;

    while (*src != '\0') {
        *dest_ptr = *src;
        src++;
        dest_ptr++;
    }

    *dest_ptr = '\0';
    return dest;
}

/**
 * my_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *my_strdup(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *dup = malloc(len + 1);

    if (dup == NULL) {
        return NULL;
    }

    memcpy(dup, str, len + 1);

    return dup;
}

/**
 * my_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void my_puts(const char *str)
{
    if (str == NULL) {
        return;
    }

    while (*str != '\0') {
        _putchar(*str);
        str++;
    }
}

/**
 * my_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(STDOUT_FILENO, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;

    return (1);
}

