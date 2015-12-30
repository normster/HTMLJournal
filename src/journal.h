#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#ifndef MAIN_H
#define MAIN_H

int new_entry(struct tm *tm);

int add_text();

int add_image(char* filename);

int add_checker();

#endif
