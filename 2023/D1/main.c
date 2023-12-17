#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>

static const uint8_t digit_array_len = 20;
static const char* const digit_array[20] = {
  "zero",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six", 
  "seven",
  "eight",
  "nine",
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

int8_t digit_map(const char* const identifier);
char* rstr(const char* const source);
uint32_t parse_line(const char* const line);
uint32_t handle_file(const char* const file_path);

int8_t
digit_map(const char* const identifier) {
  if (strncmp(identifier, "zero", 4) == 0)
    return 0;
  else if (strncmp(identifier, "one", 3) == 0)
    return 1;
  else if (strncmp(identifier, "two", 3) == 0)
    return 2;
  else if (strncmp(identifier, "three", 5) == 0)
    return 3;
  else if (strncmp(identifier, "four", 4) == 0)
    return 4;
  else if (strncmp(identifier, "five", 4) == 0)
    return 5;
  else if (strncmp(identifier, "six", 3) == 0)
    return 6;
  else if (strncmp(identifier, "seven", 5) == 0)
    return 7;
  else if (strncmp(identifier, "eight", 5) == 0)
    return 8;
  else if (strncmp(identifier, "nine", 4) == 0)
    return 9;

  if (strlen(identifier) == 1) {
    if (isdigit(identifier[0]) != 0)
      return identifier[0] - '0';
  }

  return -1;
}

char*
rstr(const char* const source) {
  const char* ptr_end_source = (source + (strlen(source) - 1));
  char* rev_source = (char*)calloc(strlen(source) + 1, sizeof(char));

  for (size_t idx = 0; idx < strlen(source); ++idx) {
    strncat(rev_source, ptr_end_source, sizeof(char));
    --ptr_end_source;
  }

  return rev_source;
}

uint32_t
parse_line(const char* const line) {
  char* calibration_val = (char*)calloc(3, sizeof(char));
  char* rline = rstr(line);

  uint8_t first_digit = 0;
  uint8_t last_digit = 0;

  size_t first_occurrence = SIZE_MAX;
  size_t last_occurrence = SIZE_MAX;

  printf("ParsingLine: %s\n", line);

  for (uint8_t idx = 0; idx < digit_array_len; ++idx) {
    const char* const digit_ref = digit_array[idx];
    char* rdigit_ref = rstr(digit_ref);
    uint8_t digit = digit_map(digit_ref);

    printf("\tDigitRef: %s\n\tRevDigitRef: %s\n", digit_ref, rdigit_ref);

    char* first_pos = strstr(line, digit_ref);

    if (first_pos != NULL) {
      printf("\t\tFound FirstPos: %s\n", digit_ref);

      size_t f_pos = first_pos - line;

      if (f_pos < first_occurrence) {
        printf("\t\t\tSet FirstDigit: %d\n", digit);

        first_occurrence = f_pos;
        first_digit = digit;
      }
    }

    char* last_pos = strstr(rline, rdigit_ref);

    if (last_pos != NULL) {
      printf("\t\tFound LastPos: %s\n", digit_ref);

      size_t l_pos = last_pos - line;
      
      if (l_pos < last_occurrence) {
        printf("\t\t\tSet LastDigit: %d\n", digit);
        
        last_occurrence = l_pos;
        last_digit = digit;
      }
    }

    free(rdigit_ref);
  }

  calibration_val[0] = '0' + first_digit;

  if (last_digit != 0)
    calibration_val[1] = '0' + last_digit;

  printf("    {\n      NumResult >>> %s\n    ", calibration_val);
  printf("  Cast NumResult >>> %lu\n    };\n", strtoul(calibration_val, NULL, 10));

  uint32_t calib_val = strtoul(calibration_val, NULL, 10);

  free(calibration_val);
  free(rline);

  return calib_val;
}

uint32_t
handle_file(const char* const file_path) {
  FILE* file = fopen(file_path, "r");

  if (file == NULL)
    return 0;

  uint32_t total = 0;
  char* buffer = NULL;
  size_t buffer_size = 0;

  while (getline(&buffer, &buffer_size, file) != -1)
    total += parse_line(buffer);

  free(buffer);
  fclose(file);

  return total;
}

int main(void) {
  uint32_t total = handle_file("input.txt");

  printf("Total >>> %" PRIu32 "\n", total);

  return 0;
}
