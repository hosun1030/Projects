#include <stdio.h>      /* needed for printf() and fprintf() */ 
#include <ctype.h>
#include "dictionary.h"

#define _DEBUG_ 0

int getIndex(char c)
{
   char c2 = tolower(c);
#if _DEBUG_
  printf("getIndex: %c --> %c\n", c, c2);
#endif
   if ( c2 == '\'') return 0;
  return (c2 - 'a')+1;
}

int isValidChar(char c)
{
   if ((c == '\'') || (c >= 'a' && c <= 'z')) return 1;

   if ((c >= 'A') && (c <= 'Z')) return 1;
   
   return 0;
}

ResultType find(dictentry *dictnode, const char *word, const char *targetword)
{

//  if (!isValidChar(*word)) return BADCHARS;

  char c = *word;
#if _DEBUG_
  printf("find: %c,target=%s\n", c, targetword);
#endif

  if (dictnode == 0) return MISSPELLED;

  if (c == 0) {
    if (dictnode->isEndofWord) return CORRECT;
    else return MISSPELLED;
  }

  int index = getIndex(c);

#if _DEBUG_
  printf("find: c=%c, index=%d\n", c, index);
#endif
  // check for next layer using recursive
  return  find (dictnode->next[index], ++word, targetword);
}

ResultType insert(dictentry *dictnode, const char *chars, const char *targetword)
{
  char c = *chars; // get the first char 

  // printf("insert: %c,target=%s\n", c, targetword);

  if (c == '\0') { // done
    if (dictnode->isEndofWord) {
      return EXISTS;
    } else {
      dictnode->isEndofWord = 1; // or TRUE
      return ADDED;
    }
  }

 int index = getIndex(c);

 if (dictnode->next[index] == 0) { // not exist, add the node
   dictentry *newdic = calloc(sizeof(dictentry), sizeof(char));
   dictnode->next[index] = newdic;
 } 
 
  // insert next char
  return insert(dictnode->next[index], ++chars, targetword);
}

#if 0 // this is for testing
int main(int argc, char **argv)
{
  dictentry *root = calloc(sizeof(dictentry), sizeof(char));
  ResultType rt = insert(root, "boy", "boy");

  printf("Insert ResutType=%d\n", rt);
  rt = find(root, "boy", "boy");
  printf("Find \"boy\" ResutType=%d\n", rt);

  rt = find(root, "bold", "bold");
  printf("Find \"bold\" ResutType=%d\n", rt);
}
#endif
