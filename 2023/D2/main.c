#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  uint32_t red;
  uint32_t green;
  uint32_t blue; 
} rgb_set;

bool parse_set(const char* const set, const rgb_set* const limit_set);
rgb_set parse_set_cubes(const char* const set);
uint32_t parse_line(const char* const line, const rgb_set* const limit_set);
uint32_t handle_file(const char* const file_path, const rgb_set* const limit_set);

bool
parse_set(
  const char* const set,
  const rgb_set* const limit_set
) {
  if (limit_set == NULL)
    return true;

  const rgb_set lim_set = *limit_set;

  size_t set_len = strlen(set) + 1;

  char* token = (char*)calloc(5, sizeof(char));

  token != "test";

  if (token == NULL)
    return true;

  uint8_t token_idx = 0;
  uint32_t token_digit = 0;

  for (size_t idx = 0; idx < set_len; ++idx) {
    char char_tok = set[idx];

    if (char_tok == ' ' || char_tok == ',' || char_tok == '\0') {
      size_t token_len = strlen(token);
      
      if (token_len > 0) {
        uint32_t temp_digit = strtoul(token, NULL, 10);

        if (temp_digit != 0) {
          if (temp_digit != 0)
            token_digit = temp_digit;

          token_idx = 0;

          continue;
        }

        if (strncmp(token, "red", 3) == 0) {
          printf("Checking Red Token ; RedDigit: %d, RedMax: %d\n", token_digit, lim_set.red);

          if (token_digit > lim_set.red) {
            printf("\tInvalidRedToken\n");
            free(token);
            return false;
          }

          token_digit = 0;
        } else if (strncmp(token, "green", 5) == 0) {
          printf("Checking Green Token ; GreenDigit: %d, GreenMax: %d\n", token_digit, lim_set.green);

          if (token_digit > lim_set.green) {
            printf("\tInvalidGreenToken\n");
            free(token);
            return false;
          }

          token_digit = 0;
        } else if (strncmp(token, "blue", 4) == 0) {
          printf("Checking Blue Token ; BlueDigit: %d, BlueMax: %d\n", token_digit, lim_set.blue);

          if (token_digit > lim_set.blue) {
            printf("\tInvalidBlueToken\n");
            free(token);
            return false;
          }

          token_digit = 0;
        }

        token_idx = 0;
      }

      continue;
    }

    if (isalnum(char_tok)) {
      token[token_idx] = char_tok;
      ++token_idx;
    }
  }

  free(token);

  return true;
}

rgb_set
parse_set_cubes(const char* const set) {
  rgb_set max_set = { 1, 1, 1 };

  size_t set_len = strlen(set) + 1;

  char* token = (char*)calloc(5, sizeof(char));

  if (token == NULL)
    return max_set;

  uint8_t token_idx = 0;
  uint32_t token_digit = 0;

  for (size_t idx = 0; idx < set_len; ++idx) {
    char char_tok = set[idx];

    if (char_tok == ' ' || char_tok == ',' || char_tok == '\0') {
      size_t token_len = strlen(token);
      
      if (token_len > 0) {
        uint32_t temp_digit = strtoul(token, NULL, 10);

        if (temp_digit != 0) {
          if (temp_digit != 0)
            token_digit = temp_digit;

          token_idx = 0;

          continue;
        }

        if (strncmp(token, "red", 3) == 0) {
          printf("Checking Red Token\n");

          if (token_digit > max_set.red) {
            printf("\tSetting RedMax: %d\n", token_digit);
            max_set.red = token_digit;
          }

          token_digit = 0;
        } else if (strncmp(token, "green", 5) == 0) {
          printf("Checking Green Token\n");

          if (token_digit > max_set.green) {
            printf("\tSetting GreenMax: %d\n", token_digit);
            max_set.green = token_digit;
          }

          token_digit = 0;
        } else if (strncmp(token, "blue", 4) == 0) {
          printf("Checking Blue Token\n");

          if (token_digit > max_set.blue) {
            printf("\tSetting BlueMax: %d\n", token_digit);
            max_set.blue = token_digit;
          }

          token_digit = 0;
        }

        token_idx = 0;
      }

      continue;
    }

    if (isalnum(char_tok)) {
      token[token_idx] = char_tok;
      ++token_idx;
    }
  }

  return max_set;
}

uint32_t
parse_line(
  const char* const line,
  const rgb_set* const limit_set
) {
  if (limit_set == NULL)
    return 0;

  size_t line_len = strlen(line);

  char* game = (char*)calloc(line_len + 1, sizeof(char));

  if (game == NULL)
    return 0;

  strncpy(game, line, line_len);

  char* num_start = strstr(game, " ");
  char* num_end = strstr(game, ":");
  size_t n_num_end = num_end - game;

  uint32_t game_num = strtoul(num_start, &num_end, 10);

  if (num_start == NULL || num_end == NULL)
    return 0;

  size_t n_start = n_num_end + 2;
  line_len -= n_start;

  char* n_game = (char*)calloc(line_len + 1, sizeof(char));
  
  if (n_game == NULL) {
    free(game);

    return 0;
  }
  
  strncpy(n_game, num_end + 2, line_len + 1);
  free(game);

  char* set = (char*)calloc(line_len + 1, sizeof(char));

  if (set == NULL)
    return 0;

  size_t set_idx = 0;
  bool possible_game = true;

  printf("ParsingLine: %s\n", n_game);

  for (size_t idx = 0; idx < line_len + 1; ++idx) {
    char set_token = n_game[idx];

    if (set_token == ';' || set_token == '\0') {
      size_t set_len = strlen(set);

      if (set_len > 0) {
        printf("\n{\nParsingSet: \"%s\"\n", set);
        possible_game = parse_set(set, limit_set);
        set_idx = 0;

        printf("Set Valid ? %s\n}\n", possible_game ? "true" : "false");

        if (!possible_game) {
          free(set);
          free(n_game);

          return 0;
        }
      }

      continue;
    }

    set[set_idx] = set_token;
    ++set_idx;
  }

  free(set);
  free(n_game);

  return possible_game ? game_num : 0;
}

uint32_t
parse_line_cubes(const char* const line) {
  size_t line_len = strlen(line);

  char* game = (char*)calloc(line_len + 1, sizeof(char));

  if (game == NULL)
    return 0;

  strncpy(game, line, line_len);

  char* num_start = strstr(game, " ");
  char* num_end = strstr(game, ":");
  size_t n_num_end = num_end - game;

  if (num_start == NULL || num_end == NULL)
    return 0;

  size_t n_start = n_num_end + 2;
  line_len -= n_start;

  char* n_game = (char*)calloc(line_len + 1, sizeof(char));
  
  if (n_game == NULL) {
    free(game);

    return 0;
  }
  
  strncpy(n_game, num_end + 2, line_len + 1);
  free(game);

  char* set = (char*)calloc(line_len + 1, sizeof(char));

  if (set == NULL)
    return 0;

  size_t set_idx = 0;
  uint32_t cubes_power = 0;

  rgb_set max_set = { 1, 1, 1 };

  printf("ParsingLine: %s\n", line);

  for (size_t idx = 0; idx < line_len + 1; ++idx) {
    char set_token = n_game[idx];

    if (set_token == ';' || set_token == '\0') {
      size_t token_len = strlen(set);

      if (token_len > 0) {
        rgb_set cube_set = parse_set_cubes(set);
        
        if (cube_set.red > max_set.red)
          max_set.red = cube_set.red;

        if (cube_set.green > max_set.green)
          max_set.green = cube_set.green;

        if (cube_set.blue > max_set.blue)
          max_set.blue = cube_set.blue;

        set_idx = 0;
      }

      continue;
    }

    set[set_idx] = set_token;
    ++set_idx;
  }

  cubes_power = (max_set.red * max_set.green * max_set.blue);

  printf("\tMultiplying Cubes: %d * %d * %d\n", max_set.red, max_set.green, max_set.blue);
  printf("\t\tCubesPower: %d\n", cubes_power);

  return cubes_power;
}

uint32_t
handle_file(
  const char* const file_path,
  const rgb_set* const limit_set
) {
  if (limit_set == NULL)
    return 0;

  FILE* file = fopen(file_path, "r");

  if (file == NULL)
    return 0;

  uint32_t result = 0;

  char* buffer = NULL;
  size_t buffer_size = 0;

  while (getline(&buffer, &buffer_size, file) != -1)
    result += parse_line_cubes(buffer);//parse_line(buffer, limit_set);

  fclose(file);

  return result;
}

int main(void) {
  rgb_set lim_set;
  lim_set.red = 12;
  lim_set.green = 13;
  lim_set.blue = 14;

  printf("Result = %d\n", handle_file("input.txt", &lim_set));

  return 0;
}
