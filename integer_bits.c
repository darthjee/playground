#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

char in(char opt, char *options);
char read_option(char *options, char* text);
void show_table(int number);
char *bit_string(unsigned char value);

int main() {
  char exit;
  int number;

  do {
    show_table(number);
    exit = read_option("ynYN", "\nDo you wanna quit? [y/n]");
  } while(! in(exit, "yY"));
}

void show_table(int number) {
  int i;
  char *array = (char *) &number;
  char sig;
  unsigned char not_sig;

  printf("Number: %d\n", number);
  printf("index\tsigned\tunsigned\n");

  for (i = 0; i < 4; i++) {
    sig = not_sig = array[i];

    printf("[%d]\t%+04d\t%03d\n", i, sig, not_sig);
  }
}

char *bit_string(unsigned char value) {
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
