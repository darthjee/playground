#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

char in(char opt, char *options);
char read_option(char *options, char* text);

int main() {
  char exit;

  do {
    exit = read_option("ynYN", "\nDo you wanna quit? [y/n]");
  } while(! in(exit, "yY"));
}

char read_option(char *options, char* text) {
  char opt;

  do {
    printf("%s", text);
    scanf("%c", &opt);
  } while (! in(opt, options));

  return opt;
}

char in(char opt, char *options) {
  int i, size;

  size = strlen(options);

  for (i = 0; i < size; i++){
    if(opt == options[i]) {
      return true;
    }
  }

  return false;
}
