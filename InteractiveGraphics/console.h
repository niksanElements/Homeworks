#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

static const WORD MAX_CONSOLE_LINES = 500;

void RedirectIOToConsole();

#endif // CONSOLE_H_
