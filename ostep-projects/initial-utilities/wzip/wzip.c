#include <stdio.h>
#include <string.h>

// TODO: Debug current algorithm

#define BUFSIZE 256

int main(int argc, char** argv) {
  if (!argv[1]) {
    printf("wzip: file1 [file2 ...]\n");
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    FILE* file = fopen(argv[i], "rb");
    char line[BUFSIZE];
    while (fgets(line, BUFSIZE, file)) {
      char zippedLine[BUFSIZE];
      char lastChar; 
      int charCounter = 1;
      for (int j = 1; j < strlen(line); j++) {
        lastChar = line[j - 1]; 
        char word[BUFSIZE];
        if (lastChar == line[j]) {
          charCounter++;
        } else {
          sprintf(word, "%d%c", charCounter, line[j]);
          strcat(zippedLine, word);
        }
      }
      fwrite(zippedLine, strlen(line), 1, stdout);
    }
  }
  return 0;
}
