#ifndef __PINFO_H
#define __PINFO_H

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void pinfo_blank();

void pinfo_pid(int pid);

char* proc_name(int pid);

#endif