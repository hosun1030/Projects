#ifndef _dictionary_h_
#define _dictionary_h_
#include<stdlib.h>
#define Nchars 27 /* a-z + ' */

typedef struct dictentry_
{
  int isEndofWord;
  struct dictentry_ *next[Nchars];
} dictentry;

typedef enum {
  CORRECT,
  MISSPELLED,
  BADCHARS,
  ADDED,
  EXISTS
} ResultType;

ResultType find(dictentry *dictnode, const char *word, const char *targetword);

ResultType insert(dictentry *dictnode, const char *characters, const char *targetword);

#endif
