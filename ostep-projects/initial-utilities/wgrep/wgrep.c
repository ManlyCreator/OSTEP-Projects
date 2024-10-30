#include <stdio.h>
#include <string.h>

#define BUFSIZE 256

void printSearchTerm(FILE* file, char* searchTerm);

int main(int argc, char** argv) {
  if (!argv[1]) {
    printf("wgrep: searchterm [file ...]\n");
    return 1;
  }
  char searchTerm[BUFSIZE];
  strcpy(searchTerm, argv[1]);
  if (argv[2]) {
    for (int i = 2; i < argc; i++) {
      FILE* file = fopen(argv[i], "r");
      if (!file) {
        printf("wgrep: cannot open file\n");
        return 1;
      }
      printSearchTerm(file, searchTerm);
      fclose(file);
    }
  } else {
    printSearchTerm(stdin, searchTerm);
  }
  return 0;
}

void printSearchTerm(FILE* file, char* searchTerm) {
  char line[BUFSIZE];
  while (fgets(line, BUFSIZE, file)) {
    int searchIdx = 0;
    int printLine = 0;
    for (int c = 0; c < strlen(line); c++) {
      if (line[c] == searchTerm[searchIdx]) {
        searchIdx++;
      } else {
        searchIdx = 0;
      }
      if (searchIdx == strlen(searchTerm)) {
        printLine = 1;
      }
    }
    if (printLine) {
      printf("%s", line);
    }
  }
}
