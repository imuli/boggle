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

Wordlist
getwords(const char *wordfile){
	FILE *fp;
	ssize_t wordsz;
	Wordlist words;
	size_t wordlen = 0;
	char *word = NULL;

	fp = fopen(wordfile, "r");
	if(fp==NULL) return NULL;

	words = wordlist_init(16);
	for(;;){
		wordsz = getline(&word, &wordlen, fp);
		if(wordsz < 1) break;
		word[wordsz-1] = '\0';
		if(board_check(word)>0)
			wordlist_add(words, word);
	};

	free(word);
	fclose(fp);
	return words;
}

int
main(int argc, char **argv){
	char *word;
	size_t wordlen = 0;
	ssize_t r;
	int i;
	Wordlist valid, user;
	FILE *wfile;

	if(argc<2){
		if(!rand_open())
			return 1;
		board_randomize();
		rand_close();
	}else{
		board_set(argv[1]);
	}

	valid = getwords("/usr/share/dict/words");
	if(valid==NULL){
		perror("getwords");
		return 1;
	}

	word = malloc(wordlen);
	user = wordlist_init(16);
	for(;;){
		printf("\ec");	/* clear screen */
		board_string();

		for(i=0;i<user->c;i++)
			printf("%s ", user->v[i]);

		r = getline(&word, &wordlen, stdin);
		if(r <= 1) break;

		word[r-1]='\0'; /* remove the newline */
		if(board_check(word) && wordlist_check(valid, word)){
			if(!wordlist_check(user, word))
				wordlist_add(user, word);
		}
	}

	for(i=0;i<valid->c;i++)
		if(!wordlist_check(user, valid->v[i]))
			printf("%s ", valid->v[i]);
	printf("\n");

	return 0;
}

