/** List of function prototypes for kc_shell by:
 * @DrKayPH
 * @Clement-tech
 * for ALX-SE simple_shell cohort 12 task
 */
#ifndef KC_SHELL_H
#define KC_SHELL_H

/* toem_parser.c */
int cmd_kc(info_t *, char *);
char *char_d(char *, int, int);
char *pathfinder(info_t *, char *, char *);

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


#endif
