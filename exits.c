#include "kc_shell.h"

/**

_strlen - returns the length of a string

@s: the string to find the length of

Return: the length of the string
*/
int _strlen(char *s)
{
int len = 0;

while (*s != '\0')
{
len++;
s++;
}

return len;

/**
 * _strchr - find the first occurrence of a character in a string
 * @s: the string to search
 * @c: the character to look for
 * Return: a pointer to the first occurrence of c in s, or NULL if not found
 */
char *_strchr(char *s, char c)
{
    while (*s != '\0') {
        if (*s == c) {
            return s;
        }
        s++;
    }
    if (c == '\0') {
        return s;
    }
    return NULL;
}

/**
 * _strlen - returns the length of a string
 * @s: the string to get the length of
 * Return: the length of the string
 */
int _strlen(char *s)
{
    int len = 0;
    while (*s != '\0')
    {
        len++;
        s++;
    }
    return len;
}
}
