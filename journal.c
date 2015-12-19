#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "journal.h"

int main(int argc, char* argv[])  {
  char* arg1 = argv[1];
  char* arg2 = argv[2];

  if (arg1 == NULL) {
    printf("Please enter a command.\n");
    return -1;
  }

  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  int day = tm->tm_mday;
  int wday = tm->tm_wday;
  int month = tm->tm_mon + 1;
  int year = tm->tm_year + 1900;
  char* new = "new";
  if (!strcmp(arg1, new)) {
    return new_entry(day, wday, month, year);
  }

  printf("\'%s\' is not a command.\n", arg1);
  return -1;
}

int new_entry(int day, int wday, int month, int year) {
  char d[10], m[10], y[10];

  sprintf(d, "%02d", day);
  sprintf(m, "%02d", month);
  sprintf(y, "%04d", year);

  // YYYYMMDD.html\0
  char* filename = malloc(sizeof(char) * 14);
  strcpy(filename, y);
  strcat(filename, m);
  strcat(filename, d);
  strcat(filename, ".html");

  printf("%s\n", filename);

  FILE* fp = fopen(filename, "r+");
  if (!fp) {
    fp = fopen(filename, "w+");
    printf("Creating new file for today. Adding new entry.\n");
  } else {
    printf("Previous file for today found. Adding new entry.\n");
  }

  char* h1;
  switch (wday) {
    case 0:
      h1 = "Sunday, ";
      break;
    case 1:
      h1 = "Monday, ";
      break;
    case 2:
      h1 = "Tuesday, ";
      break;
    case 3:
      h1 = "Wednesday, ";
      break;
    case 4:
      h1 = "Thursday, ";
      break;
    case 5:
      h1 = "Friday, ";
      break;
    case 6:
      h1 = "Saturday, ";
      break;
    default:
      return -1;
  }

  fprintf(fp, "<html>\n  <head>\n  </head>\n  <body>\n    <h1>%s</h1>\n  </body>\n</html>", h1);
  return 0;
}
