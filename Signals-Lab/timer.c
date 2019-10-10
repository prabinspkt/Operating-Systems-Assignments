/* timer.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int count = 0;

void sigint_handler(int signum) 
{
  printf("Total seconds: %d\n", count);
  exit(1);
}

void alrm_handler(int signum)
{ //signal handler
  count++;
}

int main(int argc, char * argv[])
{
  signal(SIGINT,sigint_handler); //register handler to handle SIGINT
  signal(SIGALRM,alrm_handler); //register handler to handle SIGALRM
  while(1) {
    alarm(1);
    sleep(1);
  } //busy wait for signal to be delivered
  return 0; //never reached
}