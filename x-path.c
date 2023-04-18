#include "kc_shell.h"
#include <stdlib.h>
#include <stderr.h>

/**
 * char_d - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *char_d(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/* performs any error checking to ensure that start and stop are valid indices for a "pathstr" array */

char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i, k;

    // Check that start and stop are valid indices
    if (start < 0 || start >= strlen(pathstr) || stop < 0 || stop > strlen(pathstr) || start >= stop) {
        fprintf(stderr, "Invalid start and stop indices\n");
        return NULL;
    }

    // Copy the characters into the buffer
    for (i = start, k = 0; i < stop; i++) {
        if (pathstr[i] != ':') {
            buf[k++] = pathstr[i];
        }
    }

    // Null terminate the buffer
    buf[k] = '\0';

    // Return a pointer to the buffer
    return buf;
}


/**
 * pathfinder - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *pathfinder(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (cmd_kc(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = char_d(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (cmd_kc(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}


/**
 * cmd_kc - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int cmd_kc(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

