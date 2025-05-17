#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "alias.h"


#define RC_FILE ".caliases"
#define MAX_LINE 512



void list_aliases() {
  printf("Listing your CAliases: \n\n");


  const char *home = getenv("HOME");
  
  char path[512];

  snprintf(path, sizeof(path), "%s/%s", home, RC_FILE);
  
  FILE* file = fopen(path, "r");

  if (file == NULL) {
    return;
  }

  char line[MAX_LINE];

  while (fgets(line, sizeof(line), file)) {
    Alias a = parse_alias(line);
    printf("%s -> %s", a.name, a.command);
  }

  fclose(file);
}

void remove_alias(const char* input) {

  const char *home = getenv("HOME");
  
  char path[512];

  snprintf(path, sizeof(path), "%s/%s", home, RC_FILE);

  FILE* file = fopen(path, "r");


  if (file == NULL) {
    // TODO: error handling
    return;
  }


  Alias aliases[100];
  char line[MAX_LINE];
  int alias_index = 0;
  while(fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';

    Alias a = parse_alias(line);


    if (!(strcmp(a.name, input) == 0)) {
      aliases[alias_index] = a;
      alias_index++;
    }

  }

  fclose(file);


  file = fopen(path, "w");

  if (file == NULL) {
    // TODO: TRATAR ERROS
    return;
  }

  for (int i = 0; i < alias_index; i++) {
    char buf[512];
    alias_to_str(aliases[i], buf, sizeof(buf));
    fprintf(file, "%s\n", buf);
  }

  fclose(file);
}

void add_alias(const char* input) {
  Alias alias = parse_alias(input);

  Alias aliases[100];

  const char *home = getenv("HOME");
  char path[512];
snprintf(path, sizeof(path), "%s/%s", home, RC_FILE);

  FILE* file = fopen(path, "r");

  if (file == NULL) {
    return;
  }


  int alias_index = 0;
  int replaced = 0;
  char line[512];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    Alias a = parse_alias(line);
    if (strcmp(a.name, alias.name) == 0) {
        strncpy(a.command, alias.command, MAX_COMMAND - 1);
        a.command[MAX_COMMAND - 1 ] = '\0';
        aliases[alias_index] = a;
        replaced = 1;
    } else {
        aliases[alias_index] = a;
    }

    alias_index++;

  }

  if (replaced == 0) {
      if (alias_index >= 100) {
        printf("émaior");
      } else {
          aliases[alias_index] = alias;
          alias_index++;
      }
  }

  fclose(file);

  file = fopen(path, "w");

  if (file == NULL) {
    // TODO: TRATAR ERROS
    return;
  }

  for (int i = 0; i < alias_index; i++) {
    char buf[512];
    alias_to_str(aliases[i], buf, sizeof(buf));
    fprintf(file, "%s\n", buf);

  }


  fclose(file);
}


Alias parse_alias(const char *input) {
    Alias a;
    const char *prefix = "alias ";
    size_t prefix_len = strlen(prefix);

    const char *start = input;
    if (strncmp(input, prefix, prefix_len) == 0) {
        start = input + prefix_len;
    }

    char *equal_sign = strchr(start, '=');
    if (equal_sign == NULL) {
        a.name[0] = '\0';
        a.command[0] = '\0';
        return a;
    }

    size_t name_len = equal_sign - start;
    strncpy(a.name, start, name_len);
    a.name[name_len] = '\0';

    const char *cmd = equal_sign + 1;
    strncpy(a.command, cmd, MAX_COMMAND - 1);
    a.command[MAX_COMMAND - 1] = '\0';

    return a;
}

void alias_to_str(Alias alias, char *buffer, size_t buffer_size) {
  snprintf(buffer, buffer_size, "alias %s=%s", alias.name, alias.command);
}
