#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

char in(char opt, char *options);
char read_option(char *options, char* text);
void show_table(int number);
char *bit_string(unsigned char value);
char *reverse_string(char *value);
char interact(int *number);
void change_char(int *number);
void change_number(int *number);

int main() {
  char opt;
  int number;

  do {
    show_table(number);
    opt = interact(&number);
  } while(! in(opt, "qQ"));
}

char interact(int *number) {
  char opt;

  opt = read_option("qQcCnN", "Choose an option: [Q]uit, change a [C]har, change the [N]umber\n");

  if (in(opt, "cC")) {
    change_char(number);
  } else if (in(opt, "nN")) {
    change_number(number);
  }

  return opt;
}

void show_table(int number) {
  int i;
  char *array = (char *) &number;
  char *bits, *reverse_bits;
  char sig;
  unsigned char not_sig;

  printf("Number: %d\n", number);
  printf("index\tsigned\tunsigned\tbit\t\tinverted\n");

  for (i = 0; i < 4; i++) {
    sig = not_sig = array[i];
    bits = bit_string(not_sig);
    reverse_bits = reverse_string(bits);

    printf("[%d]\t%+04d\t%03d\t\t%s\t%s\n", i, sig, not_sig, bits, reverse_bits);
  }
}

void change_char(int *number) {
  int index;
  unsigned int value;
  char *array;

  array = (char *) number;

  do {
    show_table(*number);
    printf("Which index do you wanna change?: ");
    scanf("%d", &index);
  } while (index >= sizeof(int) || index < 0);

  do {
    show_table(*number);
    value = (unsigned int) array[index];
    printf("Which should be the new value for char[%d] = %d ?\n", index, value);
    scanf("%d", &value);
  } while(value > 255);

  array[index] = (unsigned char) value;
}

void change_number(int *number) {
  unsigned int value;

  show_table(*number);
  printf("Which should be the new value for the number?\n");
  scanf("%d", number);
}

char *reverse_string(char *string) {
  int len, i;
  char *reverse;

  reverse = malloc((len + 1) * sizeof(char));
  len = strlen(string);
  reverse[8] = '\0';

  for (i = 0; i < len; i++) {
    reverse[i] = string[len - i - 1];
  }

  return reverse;
}

char *bit_string(unsigned char value) {
  char *string;
  char i;

  string = malloc(9 * sizeof(char));
  string[8] = '\0';

  for(i = 0; i < 8; i++) {
    string[i] = '0' + value % 2;
    value /= 2;
  }

  return string;
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
