#include <sys/types.h>
#include <sys/stat.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "boggle.h"

/* single threaded, yup! */
static long size;
static FILE *fp;
static char *curword;
static int curwordlen;

char *
word_next(FILE *fp, char *word, int wordlen){
  getline(&word, &wordlen, fp);
  word[strlen(word)-1]='\0';
  return word;
}

long
word_reset(FILE *fp){
  return fseek(fp, 0, SEEK_SET);
}

FILE *
word_open(const char *word){
  struct stat statb;
  FILE *fp;

  if((fp = fopen(word, "r")) == NULL)
    return NULL;
  if(fstat(fileno(fp), &statb) < 0){
    fclose(fp);
    return NULL;
  }
  size = (long)statb.st_size;

  return fp;
}

int
word_close(){
  return fclose(fp);
}

int
word_check(const char *word){
  char *match;
  int matchlen;
  long min, max;
  long off;
  int cmp, sz;

  matchlen=42;
  match=malloc(matchlen);

  min=0; max=size;

  while(off!=(min+max)/2){
    off=(min+max)/2;
    fseek(fp, off, SEEK_SET);
    getline(&match, &matchlen, fp);	/* discard the first line, may be incomplete */
    sz=getline(&match, &matchlen, fp);
    match[sz-1]='\0';	/* discard '\n' */
    cmp=strcmp(match, word);
    /*    fprintf(stderr, "%s, %d, %d, %d\n", match, min, max, cmp);*/
    if(cmp==0){
      free(match);
      return 1;
    }
    if(cmp<0) min=off;
    if(cmp>0) max=off;
  }
  free(match);
  return -1;
}

