#ifndef __SIGNALHANDLER_H
#define __SIGNALHANDLER_H

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void bg_signal_handler(int sig);

void cntrl_C_handler(int sig);

void cntrl_Z_handler(int sig);

#endif