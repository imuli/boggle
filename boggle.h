
int board_randomize();
char *board_string();
int board_check(char *);

int rand_close();
int rand_open();
long rand_tiny();

char *word_next(FILE *, char *, int);
long word_reset(FILE *);
FILE *word_open();
int word_close();
int word_check(const char *);
