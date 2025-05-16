#include <stdio.h>
#include <string.h>
#include "alias.h"

#define EXIT_SUCCESS 0

int main(int argc, char *argv[])
{

  printf("\n");

  // print all user arguments (just for development)
  for (int i = 0; i < argc; i++) {
    printf("arg[%d] = %s \n", i, argv[i]);
  }

  // check if the program was ran with at least 1 arg
  if (argc < 2) {
    printf("O MEU ALIADO O PROGRAMA PRECISA DE ARGS \n");
    return 1;
  }




  // check for user options

  if (strcmp(argv[1], "list") == 0) {
    list_aliases();
  }

  if (strcmp(argv[1], "add") == 0){
    if (argc < 3) {
      printf("You should pass the alias in format:\n\n alias=\"command\" \n");
      return 1;
    } else {
      // TODO: create alias logic here!
      //
      // check if there is mutilple aliases, so check all and add then to a file
      // eg.: calias add ls="ls --color=auto" gs="git status"
      //
      // create a ".calias" containing aliases created by calias
      //
      // then, users should import it in bashrc/zshrc file
      //

      printf("hmmm daora, bom aliase meu patrao :+1: \n");
    }
  }
  return EXIT_SUCCESS;
}

