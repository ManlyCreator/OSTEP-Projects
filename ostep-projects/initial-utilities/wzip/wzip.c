#include <stdio.h>

#define BUFSIZE 256

int main(int argc, char** argv) {
  if (!argv[1]) {
    printf("wzip: file1 [file2 ...]\n");
    return 1;
  }
  char currentChar;
  char lastChar;
  int charOccurrences = 1;
  int ctr = 0;
  for (int i = 1; i < argc; i++) {
    FILE* file = fopen(argv[i], "rb");
    if (!file) {
      printf("wzip: error opening file\n");
      return 1;
    }
    while (fread(&currentChar, 1, 1, file)) {
      // If the last character and character are equal,
      // increment the occurrences
      if (currentChar == lastChar) {
        charOccurrences++;
      // Otherwise, print the last character and its number
      // of occurrences as long as ctr > 0 
      // (ensures that the first character is properly counted)
      } else if (ctr > 0) {
        fwrite(&charOccurrences, 4, 1, stdout);
        fwrite(&lastChar, 1, 1, stdout);
        charOccurrences = 1;
      }
      lastChar = currentChar;
      ctr++;
    }
  }
  // The last character will never be printed in the loop,
  // so it is printed afterwards
  fwrite(&charOccurrences, 4, 1, stdout);
  fwrite(&lastChar, 1, 1, stdout);
  return 0;
}
