#ifndef __HISTORY_H
#define __HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

void printHistory();

void updateHistory(char* inputCommand, int *tot);

void updateToFile(char* hist_file_loc);

void readFromFile(char* hist_file_loc);

void historyCheck();

#endif


