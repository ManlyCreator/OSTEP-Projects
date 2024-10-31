#include <stdio.h>
#include <string.h>

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
      return 1;
    }
    char character[2];
    char lastChar[2] = "";
    int charOccurrences = 1;
    char occurrencesBuffer[BUFSIZE];
    int ctr = 0;
    while (fread(character, 1, 1, file)) {
      // If the last character and character are equal,
      // increment the occurrences
      if (strcmp(lastChar, character) == 0) {
        charOccurrences++;
      // Otherwise, print the last character and its number
      // of occurrences as long as ctr > 0 
      // (ensures that the first character is properly counted)
      } else if (ctr > 0) {
        // occurrences is printed to a string buffer so 
        // it can be printed through fwrite
        sprintf(occurrencesBuffer, "%d", charOccurrences); 
        fwrite(occurrencesBuffer, 4, 1, stdout);
        fwrite(lastChar, 1, 1, stdout);
        charOccurrences = 1;
      }
      strcpy(lastChar, character);
      ctr++;
    }
    // The last character will never be printed in the loop,
    // so it is printed afterwards
    sprintf(occurrencesBuffer, "%d", charOccurrences); 
    fwrite(occurrencesBuffer, 4, 1, stdout);
    fwrite(lastChar, 1, 1, stdout);
  }
  return 0;
}
