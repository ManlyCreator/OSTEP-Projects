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
    if (!file) {
      printf("wzip: error opening file\n");
    }
    char character[2];
    char lastCharacter[2] = "";
    int characterCounter = 1;
    char zippedLine[BUFSIZE] = "";
    char word[BUFSIZE];
    while (fread(character, 1, 1, file)) {
      if (strcmp(lastCharacter, "") != 0 && strcmp(character, lastCharacter) == 0) {
        characterCounter++;
      } else {
        sprintf(word, "%d", characterCounter);
        fwrite(word, 1, 1, stdout);
        fwrite(character, 1, 1, stdout);
        characterCounter = 1;
      }
      strcpy(lastCharacter, character);
    }
  }
  return 0;
}
