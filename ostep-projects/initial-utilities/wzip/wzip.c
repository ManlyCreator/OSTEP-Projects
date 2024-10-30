#include <stdio.h>
#include <string.h>

// TODO: Write to stdout using the specified algorithm
// in binary format

int main(int argc, char** argv) {
  if (!argv[1]) {
    printf("wzip: file1 [file2 ...]\n");
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    FILE* file = fopen(argv[i], "rb");
    char line[256];
    fgets(line, 256, file);
    fwrite(line, strlen(line), 1, stdout);
  }
  return 0;
}
