/* DISCLAIMER */
/* I have been doing ruby for too
 * long and forgot to free the memory after mallocs XD */

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
void show_byte(int index, char byte);

int main() {
  char opt;
  int number;

  do {
    /* show the table on every interaction*/
    show_table(number);

    /* interact with the user to either change values or quit*/
    opt = interact(&number);
  } while(! in(opt, "qQ"));
}

char interact(int *number) {
  char opt;

  /* options are quit, change a char or change the number as a whole */
  opt = read_option("qQcCnN", "Choose an option: [Q]uit, change a [C]har, change the [N]umber\n");

  if (in(opt, "cC")) {
    change_char(number);
  } else if (in(opt, "nN")) {
    change_number(number);
  }
  /* when Q is chosen, it is time to quit */

  return opt;
}

void show_table(int number) {
  int i;
  char *array = (char *) &number;

  /* headers include the number and table headers */
  printf("Number: (signed) %+d\t(unsigned) %u\n", number, (unsigned int) number);
  printf("index\tsigned\tunsigned\tbit\t\tinverted\n");

  /* break down of each byte */
  for (i = 0; i < 4; i++) {
    show_byte(i, array[i]);
  }
}

void show_byte(int index, char byte) {
  unsigned char unsigned_byte;
  char *bits, *reverse_bits;

  unsigned_byte = (unsigned char) byte;

  /* string of bits in computacional order */
  bits = bit_string(unsigned_byte);

  /* string of bits in regular matematical order */
  reverse_bits = reverse_string(bits);

  printf(
      "[%d]\t%+04d\t%03d\t\t%s\t%s\n",
      index, byte, unsigned_byte,
      bits, reverse_bits
      );
}

/* interact to change a char / byte */
void change_char(int *number) {
  int index;
  unsigned int value;
  char *array;

  array = (char *) number;

  /* index selection */
  do {
    show_table(*number);
    printf("Which index do you wanna change?: ");
    scanf("%d", &index);
  } while (index >= sizeof(int) || index < 0);

  /* value selection */
  do {
    show_table(*number);
    value = (unsigned int) array[index];
    printf("Which should be the new value for char[%d] = %d ? (0 - 255)\n", index, value);
    scanf("%d", &value);
  } while(value > 255);

  /* assign to correct memory position whitin the integer */
  array[index] = (unsigned char) value;
}

/* interact to change the number as a whole */
void change_number(int *number) {
  unsigned int value;

  show_table(*number);
  printf("Which should be the new value for the number?\n");
  scanf("%d", number);
}

/* reverse a string */
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

/* convert a number into a string of bits */
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

/* read an option from the input and repeat until one of
 * the given options are accepted */
char read_option(char *options, char* text) {
  char opt;

  do {
    printf("%s", text);
    /* swallow <ENTER> to avoid double question */
    do {
      scanf("%c", &opt);
    } while(opt == '\n');
  } while (! in(opt, options));

  return opt;
}

/* Checks is a character exists within a given string */
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
