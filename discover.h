#ifndef __DISCOVER_H
#define __DISCOVER_H

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void plain_discover(char* current_directory, char* temp);

void plain_discover_2(char *current_directory, char *tempp);

int discover_file_directory(char* current_directory, char* tempp, char* file_name);

int discover_file_directory_2(char *current_directory, char *tempp, char *file_name);

void discover_d(char* current_directory, char* tempp);

void discover_d_2(char* current_directory, char* tempp);

void discover_f(char* current_directory, char* tempp);

void discover_f_2(char *current_directory, char *tempp);

#endif