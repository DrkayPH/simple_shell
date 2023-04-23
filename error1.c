#include "kc_shell.h"

/**
 * max_int - returns the maximum value in an array of integers
 * @arr: the array of integers
 * @size: the size of the array
 * Return: the maximum value in the array
 */
int max_int(int *arr, size_t size)
{
    int max_val = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: void
 */
void print_error(info_t *info, char *estr)
{
	fprintf(stderr, "%s: %d: %s: %s\n", info->fname, info->line_count,
	        info->argv[0], estr);
}

/**
 * print_x - function prints a hexadecimal (base 16) number
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_x(unsigned int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int current, mask = 0xF0000000;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	for (i = 7; i >= 0; i--)
	{
		current = (input & mask) >> (i * 4);
		if (current > 9)
			__putchar('a' + current - 10);
		else
			__putchar('0' + current);
		mask >>= 4;
		count++;
	}
	return (count);
}

/**
 * get_array_average - calculates the average of the elements in an integer array
 * @arr: the integer array
 * @size: the size of the array
 *
 * Return: the average of the elements in the array as a double
 */
double get_array_average(int arr[], int size)
{
    int sum = 0;
    double avg = 0.0;

    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    avg = (double) sum / size;

    return avg;
}

/**
 * string_to_lower - convert a string to lowercase
 * @str: the string to convert
 *
 * Return: a pointer to the modified string
 */
char *string_to_lower(char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] += 32;
        }
    }

    return str;
}

