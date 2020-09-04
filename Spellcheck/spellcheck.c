#include <stdio.h>      /* needed for printf() and fprintf() */ 
#include <string.h> 
#include "dictionary.h"

#define _DEBUG_ 0

const char *separators ="\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";

// check the spell for the given text file against the dictionary tree
void spellCheck(dictentry* root, char* filename)
{
  // print MISSPELLED ones (not in the dictionary) to stdout
  
  // printf("checking: %s\n", filename);
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("fopen fail");
    return;
  }

  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, fp)) != -1) {
#if _DEBUG_
    printf("LINE(%zu): %s", len, line);
#endif
    char *token = (char*)strtok(line, separators); 

    while (token != NULL)
    {
      ResultType rt = find(root, token, token);
      if (rt != CORRECT) {
         printf("%s\n", token);
      }
#if _DEBUG_
      else {
         printf("CORRECT: \"%s\"\n", token);
      }
#endif
      token = strtok(NULL, separators);
     }
  }
 
}

// build a dictionary tree from the give text file
dictentry* buildDictionaryTree(char *filename)
{
  // printf("building dictionary with: %s\n", filename);
  dictentry *root = calloc(sizeof(dictentry), sizeof(char));
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("fopen fail");
    return NULL;
  }

  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, fp)) != -1) {
    char *token = (char*)strtok(line, separators); 

    while (token != NULL)
    {
      ResultType rt = insert(root, token, token);
      if (rt != ADDED && rt != EXISTS) {
         printf("ERROR: insert fail %d for \"%s\"\n", rt, token);
      }

#if _DEBUG_
      if (rt == ADDED) {
         printf("ADDED: \"%s\"\n", token);
      }
#endif
      token = strtok(NULL, separators);
     }
  }
 
  return root;
}

int main(int argc, char **argv)
{
  if (argc != 3) {
    printf("Usage: %s check_filename dictionaray_filename\n", argv[0]);
    return -1;
  }


  dictentry* root = buildDictionaryTree(argv[2]); // aspell_list_en.txt
  if (root == NULL) {
    return -1; // TODO: error message
  }

  spellCheck(root, argv[1]); // Austen-Pride-and-Prejudice.txt
  
}
