#ifndef __LS_H
#define __LS_H

#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void plain_ls(char* current_directory);

void ls_a(char* current_directory);

void ls_l(char* current_directory);

void ls_la_al(char* current_directory);

void permission(char *filePath);

#endif