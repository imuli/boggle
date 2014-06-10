#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boggle.h"

enum {
	Wordlen = 41,
};

typedef struct wordlist *Wordlist;
struct wordlist {
  char **v;
  int c,max;
};

Wordlist
wordlist_init(int n){
  Wordlist r;
  r=malloc(sizeof(*r));
  r->v=malloc(sizeof(*r->v)*n);
  r->c=0;
  r->max=n;
  return r;
}

int
wordlist_add(Wordlist r, char *s){
  if(r->c==r->max){
    r->max*=2;
    r->v=realloc(r->v, sizeof(*r->v)*r->max);
  }
  r->v[r->c]=strdup(s);
  r->c++;
  return 1;
}

int
wordlist_check(Wordlist r, char *s){
  int i;
  for(i=0;i<r->c;i++)
    if(strcmp(s,r->v[i])==0)
      return 1;
  return 0;
}

int
main(int argc, char **argv){
  char word[Wordlen];
  int r, i;
  Wordlist wordlist;
  FILE *wfile;

  if(argc<2){
    if(!rand_open())
      return 1;
    board_randomize();
    rand_close();
  }else{
    board_set(argv[1]);
  }
   
  wfile = word_open("/usr/share/dict/words");

/* init wordlist */
  if(wfile==NULL){
	perror("word_open");
	return 1;
  }
  do{
    word_next(wfile, word, sizeof(word));
    if(strlen(word)>=3)
      if(board_check(word)>0)
	printf("%s ",word);
  }while(*word!='\0');
  printf("\n");
  fflush(stdin);

  return 0;

  for(;;){
    printf("\ec");	/* clear screen */
    board_string();
    for(i=0;i<wordlist->c;i++)
      printf("%s ", wordlist->v[i]);
//    r = getline(&word, &wordlen, stdin);
    word[r-1]='\0'; /* remove the newline */
    if(*word=='\0') break;
    if(strlen(word)>=3 && board_check(word)>0 && word_check(word)>0){
      if(!wordlist_check(wordlist, word))
	wordlist_add(wordlist, word);
    } else {
      printf("xxx\n");
    }
  }
  free(word);

  word_close();
  return 0;
}

