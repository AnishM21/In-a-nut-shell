#ifndef __FOREGROUND_H
#define __FOREGROUND_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void fore(char process[][1000], int n);

void bg(char process[][1000], int n);

void f2(char process[][1000], int n);

#endif