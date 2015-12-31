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
  char* image = "image";
  char* text = "text";
  if (!strcmp(arg1, new)) {
    return new_entry(tm);
  } else if (!strcmp(arg1, image)) {
    if (add_checker()) {
      return -1;
    }
    return add_image(arg2);
  } else if (!strcmp(arg1, text)) {
    if (add_checker()) {
      return -1;
    }
    return add_text();
  } else {
    printf("\'%s\' is not a valid command.\n", arg1);
    return -1;
  }
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
    sprintf(h1, "%s %s %d, %4d", h1_wd, h1_m, tm->tm_mday, (tm->tm_year+1900));
    fprintf(fp, "<h1>%s</h1>\n", h1);
  }

  int pm = 0;
  if (tm->tm_hour > 12) {
    pm = 1;
  }

  if (pm) {
    fprintf(fp, "<h2>%d:%02d pm<h2>\n", tm->tm_hour - 12, tm->tm_min);
  } else {
    fprintf(fp, "<h2>%d:%02d am<h2>\n", tm->tm_hour, tm->tm_min);
  }
  fclose(fp);

  FILE* curr_file = fopen(".current", "w");
  fprintf(curr_file, "%s", filename);
  fclose(curr_file);
  return 0;
}

int add_image(char* filename) {
  if (access(filename, F_OK) == -1) {
    printf("Input file does not exist.\n");
    return -1;
  }
  FILE* curr_file = fopen(".current", "r");
  char current[15];
  fread(current, 1, 14, curr_file);
  FILE* fp = fopen(current, "a");
  printf("Adding new image.\n");
  fprintf(fp, "<img src=\"%s\">\n", filename);
  fclose(fp);
  fclose(curr_file);
  return 0;
}

int add_text() {
  char* lineptr = NULL;
  size_t n = 0;
  ssize_t a = -1;
  printf("Please enter text:\n");
  while ((a = getline(&lineptr, &n, stdin)) <= 1) {
    printf("Invalid text entry. Please try again:\n");
  }
  lineptr[a-1] = 0;

  FILE* curr_file = fopen(".current", "r");
  char current[15];
  fread(current, 1, 14, curr_file);
  FILE* fp = fopen(current, "a");
  printf("\nAdding text.\n");
  fprintf(fp, "<p>%s</p>\n", lineptr);
  fclose(fp);
  fclose(curr_file);
  return 0;
}

int add_checker() {
  if (access(".current", F_OK) == -1) {
    printf("No previous entry to append to.\n");
    return -1;
  }
  FILE* curr_file = fopen(".current", "r");
  char current[20];
  fread(current, 1, 14, curr_file);
  if (!strlen(current)) {
    printf("No previous entry to append to.\n");
    return -1;
  }
  fclose(curr_file);
  return 0;
}
