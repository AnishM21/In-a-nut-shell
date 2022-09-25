#ifndef __PROMPT_H
#define __PROMPT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <stdbool.h>
#include <string.h>

char* host_name();

void prompt();

#endif