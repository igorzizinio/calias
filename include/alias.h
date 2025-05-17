#ifndef ALIAS_H
#define ALIAS_H


// TODO: in future it can be dynamic! :)

#define MAX_ALIAS_NAME 64
#define MAX_COMMAND 256
#define MAX_ALIASES 100

typedef struct {
  char name[MAX_ALIAS_NAME];
  char command[MAX_COMMAND]
} Alias;

void list_aliases();
void add_alias(const char* alias);
void remove_alias(const char* input);
Alias parse_alias(const char* input);
void alias_to_str(Alias a, char *buffer, size_t buffer_size);

#endif
