#ifndef __CD_H
#define __CD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>

void checkDir(char* arr, char* current_directory, char* previous_directory);

void changePrevDir(char* previous_directory);

void changeCurrDir(char* current_directory, char* pseudo_home, char* previous_directory);

void updateCurrDir(char* current_directory, char* previous_directory);


#endif