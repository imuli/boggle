#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int randfd;

int
rand_open(){
  randfd=open("/dev/urandom", O_RDONLY);
  if(randfd<0)
    return 0;
  return 1;
}

int
rand_close(){
  return close(randfd);
}

long
rand_tiny(long n){
  long max;
  unsigned char r[1];
  max = UCHAR_MAX+1;
  max -= max % n;
  do{
    if(!read(randfd, r, 1))
      return -1;
  }while(*r>=max);
  return *r%n;
}


