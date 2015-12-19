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

  char* new = "new";
  if (!strcmp(arg1, new)) {
    return new_entry(tm);
  }

  printf("\'%s\' is not a command.\n", arg1);
  return -1;
}

int new_entry(struct tm *tm) {
  char d[10], m[10], y[10];

  sprintf(d, "%02d", tm->tm_mday);
  sprintf(m, "%02d", (tm->tm_mon + 1));
  sprintf(y, "%04d", (tm->tm_year + 1900));

  // YYYYMMDD.html\0
  char* filename = malloc(sizeof(char) * 14);
  strcpy(filename, y);
  strcat(filename, m);
  strcat(filename, d);
  strcat(filename, ".html");

  FILE* fp = fopen(filename, "r+");
  if (!fp) {
    fp = fopen(filename, "w+");
    printf("Creating new file for today. Adding new entry.\n");
    char* h1_wd;
    switch (tm->tm_wday) {
      case 0:
        h1_wd = "Sunday";
        break;
      case 1:
        h1_wd = "Monday";
        break;
      case 2:
        h1_wd = "Tuesday";
        break;
      case 3:
        h1_wd = "Wednesday";
        break;
      case 4:
        h1_wd = "Thursday";
        break;
      case 5:
        h1_wd = "Friday";
        break;
      case 6:
        h1_wd = "Saturday";
        break;
      default:
        return -1;
    }

    char* h1_m;
    switch (tm->tm_mon) {
      case 0:
        h1_m = "January";
        break;
      case 1:
        h1_m = "February";
        break;
      case 2:
        h1_m = "March";
        break;
      case 3:
        h1_m = "April";
        break;
      case 4:
        h1_m = "May";
        break;
      case 5:
        h1_m = "June";
        break;
      case 6:
        h1_m = "July";
        break;
      case 7:
        h1_m = "August";
        break;
      case 8:
        h1_m = "September";
        break;
      case 9:
        h1_m = "October";
        break;
      case 10:
        h1_m = "November";
        break;
      case 11:
        h1_m = "December";
        break;
      default:
        return -1;
    }
    char* h1;
    sprintf(h1, "%s, %s %2d, %4d", h1_wd, h1_m, tm->tm_mday, (tm->tm_year+1900));
    fprintf(fp, "<html>\n  <head>\n  </head>\n  <body>\n    <h1>%s</h1>\n  </body>\n</html>", h1);
  } else {
    printf("Previous file for today found. Adding new entry.\n");
  }
  return 0;
}
