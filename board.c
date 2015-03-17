#include <stdio.h>
#include <string.h>

#include "boggle.h"

static char board[16];

static const char *cubes[16] = {
	"ednosw", "aaciot", "acelrs", "ehinps",
	"eefhiy", "elpstu", "acdemp", "gilruw",
	"egkluy", "ahmors", "abilty", "adenvz",
	"bfiorx", "dknotu", "abjmoq", "egintv"
};

int
board_set(char *it){
	if(strlen(it)<16)
		return -1;
	memcpy(board, it, 16);
	return 1;
}

int
board_randomize(){
	char used[16];
	int i,j,r;

	for(i=0;i<16;i++) used[i]=0;
	for(i=16;i>0;i--){
		r = rand_tiny(i);
		if(r<0) return -1;
		for(j=-1;j<r;){
			j++;
			if(used[j]==1) r++;
		}
		used[j]=1;
		r=rand_tiny(6);
		board[16-i]=*(cubes[j]+r);
	}
	return 1;
}

char *
board_string(){
	int i;

	for(i=0;i<4;i++)
		printf("%c %c %c %c\n", board[4*i], board[4*i+1], board[4*i+2], board[4*i+3]);
	return NULL;
}

static const char *adjacent[17]={
	"bef", "acefg", "bdfgh", "cgh",
	"abfij", "abcegijk", "bcdfhjkl", "cdgkl",
	"efjmn", "efgikmno", "fghjlnop", "ghkop",
	"ijn", "ijkmo", "jklnp", "klo",
	"abcdefghijklmnop"
};
static int
board_word(char *word, int position, char *used){
	const char *p;
	char letter;

	if(used[position]==1)
		return 0;

	used[position]=1;
	letter = word[0];
	if(word[0]=='\0')
		return 1;
	if(letter == 'q' && word[1] == 'u')
		word++;

	for(p=adjacent[position];*p!='\0';p++){
		if(board[*p-'a']==letter && board_word(word+1,*p-'a',used))
			return 1;
	}
	used[position]=0;
	return 0;
}

int
board_check(char *word){
	char used[17];
	memset(used, 0, 17);
	if(strlen(word) < 3) return 0;
	return board_word(word, 16, used);
}
