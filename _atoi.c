#include "kc_shell.h"

/**
 * is_interactive - checks if the shell is in interactive mode
 * @info: pointer to struct address containing shell information
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
    int stdin_fileno = fileno(stdin); // Get the file descriptor for stdin

    // Check if stdin is a terminal device and readfd is <= 2
    if (isatty(stdin_fileno) && info->readfd <= 2) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * is_delimiter - checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, const char *delim)
{
    const char *p = delim;
    while (*p) {
        if (*p++ == c) {
            return 1;
        }
    }
    return 0;
}

/**
 * is_alpha - checks for alphabetic character
 * @c: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alpha(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * my_atoi - converts a string to an integer
 * @s: The string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int my_atoi(char *s)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++) {
        if (s[i] == '-') {
            sign *= -1;
        }

        if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
    }

    if (sign == -1) {
        output = -result;
    } else {
        output = result;
    }

    return output;
}

