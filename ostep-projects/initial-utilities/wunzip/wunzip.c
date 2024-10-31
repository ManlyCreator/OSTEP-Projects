#include <stdio.h>

int main(int argc, char** argv) {
  if (!argv[1]) {
    printf("wunzip: file1 [file2 ...]\n");
    return 1;
  }
  int numChars;
  char currentChar;
  for (int i = 1; i < argc; i++) {
    FILE* file = fopen(argv[i], "rb");
    if (!file) {
      printf("wunzip: error opening file\n");
      return 1;
    }
    // Reads the file in 4-byte increments into an int
    while (fread(&numChars, 4, 1, file)) {
      // Reads another 1-byte into a char
      fread(&currentChar, 1, 1, file);
      // Writes the char to stdout int number of times
      for (int i = 0; i < numChars; i++) {
        fwrite(&currentChar, 1, 1, stdout);
      }
    }
  }
}
