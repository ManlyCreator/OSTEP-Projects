#include <stdio.h>

#define BUFSIZE 256

int main(int argc, char** argv) {
  if (!argv[1]) {
    return 0;
  }
  for (int i = 1; i < argc; i++) {
    FILE* file = fopen(argv[i], "r");
    if (file == NULL) {
      printf("wcat: cannot open file\n");
      return 1;
    }
    char buffer[BUFSIZE];
    while (fgets(buffer, BUFSIZE, file)) {
      printf("%s", buffer);
    }
    fclose(file);
  }
  return 0;
}
