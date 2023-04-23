#include "kc_shell.h"

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strncat - concatenates two strings, but limits the number of bytes copied
 * @dest: the destination buffer
 * @src: the source buffer
 * @n: the maximum number of bytes to copy
 *
 * Return: pointer to destination buffer
 */
char *_strncat(char *dest, char *src, size_t n)
{
    char *ret = dest;

    while (*dest)
        dest++;
    while (*src && n--)
        *dest++ = *src++;
    *dest = '\0';
    return (ret);
}

/**
 * _custom_atoi - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: integer value of string
 */
int _custom_atoi(char *str)
{
    int num = 0, sign = 1;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    while (*str)
    {
        if (*str >= '0' && *str <= '9')
            num = num * 10 + (*str - '0');
        else
            break;
        str++;
    }

    return sign * num;
}

/**
 * _custom_strcmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: 0 if s1 and s2 are equal, a negative value if s1 is less than s2,
 *         or a positive value if s1 is greater than s2
 */
int _custom_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}



/**
 * _custom_strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int _custom_strlen(char *str)
{
    int length = 0;
    while (*str++)
        length++;
    return length;
}

