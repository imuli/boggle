#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boggle.h"

typedef struct strv *Strv;
struct strv {
  char **v;
  int c,max;
};

Strv
strv_init(int n){
  Strv r;
  r=malloc(sizeof(*r));
  r->v=malloc(sizeof(*r->v)*n);
  r->c=0;
  r->max=n;
  return r;
}

int
strv_add(Strv r, char *s){
  if(r->c==r->max){
    r->max*=2;
    r->v=realloc(r->v, sizeof(*r->v)*r->max);
  }
  r->v[r->c]=strdup(s);
  r->c++;
  return 1;
}

int
strv_check(Strv r, char *s){
  int i;
  for(i=0;i<r->c;i++)
    if(strcmp(s,r->v[i])==0)
      return 1;
  return 0;
}

int
main(int argc, char **argv){
  char *word;
  int wordlen, r, i;
  Strv wordlist;

  if(argc<2){
    if(!rand_open())
      return 1;
    board_randomize();
    rand_close();
  }else{
    board_set(argv[1]);
  }
   
  word_open("/usr/share/dict/words");

  wordlen=41;
  word=malloc(wordlen);
  wordlist=strv_init(16);

  for(;;){
    printf("\ec");	/* clear screen */
    board_string();
    for(i=0;i<wordlist->c;i++)
      printf("%s ", wordlist->v[i]);
    r = getline(&word, &wordlen, stdin);
    word[r-1]='\0'; /* remove the newline */
    if(*word=='\0') break;
    if(strlen(word)>=3 && board_check(word)>0 && word_check(word)>0){
      if(!strv_check(wordlist, word))
	strv_add(wordlist, word);
    } else {
      printf("xxx\n");
    }
  }
  free(word);

  word_reset();
  do{
    word=word_next();
    if(strlen(word)>=3)
      if(board_check(word)>0)
	if(!strv_check(wordlist,word))
	  printf("%s ",word);
  }while(*word!='\0');
  printf("\n");
  word_close();
  return 0;
}

