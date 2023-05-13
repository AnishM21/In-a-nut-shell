#ifndef __EXECUTE_H
#define __EXECUTE_H

#include "prompt.h"
#include "pinfo.h"
#include "pwd.h"
#include "echo.h"
#include "cd.h"
#include "ls.h"
#include "history.h"
#include "discover.h"
#include "signalHandler.h"
#include "foreground.h"
#include <sys/utsname.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "jobs.h"
#include "sig_func.h"
#include "fg.h"
#include "piping.h"

void execute();

void execute_piping();

#endif