#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
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
  char* addi = "addi";
  char* addt = "addt";
  if (!strcmp(arg1, new)) {
    return new_entry(tm);
  } else if (!strcmp(arg1, addi)) {
    return add_image(arg2);
  } else if (!strcmp(arg1, addt)) {
    return add_text(arg2);
  }

  printf("\'%s\' is not a valid command.\n", arg1);
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

  FILE* fp;
  if(access(filename, F_OK) != -1) {
    //exists
    fp = fopen(filename, "a");
    printf("Previous file for today found. Adding new entry.\n");
  } else {
    //doesnt exist
    fp = fopen(filename, "a");
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
    sprintf(h1, "%s %s %2d, %4d", h1_wd, h1_m, tm->tm_mday, (tm->tm_year+1900));
    fprintf(fp, "<h1>%s</h1>\n", h1);
  }

  fprintf(fp, "<h2>%d:%2d<h2>", tm->tm_hour, tm->tm_min);
  fclose(fp);
  return 0;
}

int add_image(char* filename) {

  return 0;
}

int add_text(char* filename) {

  return 0;
}
