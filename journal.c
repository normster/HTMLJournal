#include <stdio.h>
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

  if (day < 10) {
    sprintf(d, "0%d", day);
  } else {
    sprintf(d, "%d", day);
  }
  if (month < 10) {
    sprintf(m, "0%d", month);
  } else {
    sprintf(m, "%d", month);
  }
  sprintf(y, "%d", year);

  char* filename;
  strcpy(filename, y);
  strcat(filename, m);
  strcat(filename, d);
  strcat(filename, ".html");

  printf("%s\n", filename);

  FILE* fp = fopen(filename, "r+");
  printf("Previous file for today found. Adding new entry.\n");
  if (!fp) {
    fp = fopen(filename, "w+");
    printf("Creating new file for today. Adding new entry.\n");
    char* h1;
    switch (wday) {
      case 0:
        h1 = "Sunday, ";
      case 1:
        h1 = "Monday, ";
      case 2:
        h1 = "Tuesday, ";
      case 3:
        h1 = "Wednesday, ";
      case 4:
        h1 = "Thursday, ";
      case 5:
        h1 = "Friday, ";
      case 6:
        h1 = "Saturday, ";
      default:
        return -1;
    }

    fprintf(fp, "<html>\n  <head>\n  </head>\n  <body>\n    <h1>%s</h1>\n  </body>\n</html>", h1);
  }
  return 0;
}
