#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#ifndef MAIN_H
#define MAIN_H

void new_entry(struct tm *tm);

void add_text();

void add_image(char* filename);

int add_checker();

#endif
