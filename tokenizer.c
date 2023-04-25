#include "kc_shell.h"

/**
 * **my_strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **my_strtow(char *str, char *d)
{
    int i, j, k, m, numwords = 0;
    char **s;

    if (str == NULL || str[0] == 0)
        return NULL;
    if (!d)
        d = " ";
    for (i = 0; str[i] != '\0'; i++)
        if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
            numwords++;

    if (numwords == 0)
        return NULL;
    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return NULL;
    for (i = 0, j = 0; j < numwords; j++)
    {
        while (is_delim(str[i], d))
            i++;
        k = 0;
        while (!is_delim(str[i + k], d) && str[i + k])
            k++;
        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return NULL;
        }
        for (m = 0; m < k; m++)
            s[j][m] = str[i++];
        s[j][m] = 0;
    }
    s[j] = NULL;
    return s;
}

int is_delim(char c, char *d)
{
    int i;
    for (i = 0; d[i] != '\0'; i++)
        if (c == d[i])
            return 1;
    return 0;
}

/**
 * split_string - splits a string into words using a delimiter
 * @str: the input string
 * @delim: the delimiter
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string(char *str, char delim)
{
    int i, j, k, num_words = 0;
    char **words;

    if (str == NULL || str[0] == '\0')
        return (NULL);

    // Count the number of words in the string
    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] != delim && str[i + 1] == delim) ||
            (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
        {
            num_words++;
        }
    }

    if (num_words == 0)
        return (NULL);

    // Allocate memory for the array of words
    words = (char **) malloc((num_words + 1) * sizeof(char *));
    if (words == NULL)
        return (NULL);

    // Split the string into words and store them in the array
    for (i = 0, j = 0; j < num_words; j++)
    {
        // Skip over delimiters
        while (str[i] == delim && str[i] != '\0')
            i++;

        // Count the length of the next word
        k = 0;
        while (str[i + k] != delim && str[i + k] != '\0')
            k++;

        // Allocate memory for the word
        words[j] = (char *) malloc((k + 1) * sizeof(char));
        if (words[j] == NULL)
        {
            // Free memory for all previously allocated words
            for (k = 0; k < j; k++)
                free(words[k]);

            // Free memory for the array of words
            free(words);
            return (NULL);
        }

        // Copy the characters of the word into the newly allocated memory
        for (k = 0; str[i] != delim && str[i] != '\0'; i++, k++)
            words[j][k] = str[i];
        words[j][k] = '\0';
    }

    // Add a NULL terminator to the end of the array
    words[j] = NULL;

    return words;
}

