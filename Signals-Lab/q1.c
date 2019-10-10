/* The version of signal.c which prints only once, not recursively. */
/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  exit(1); //exit after printing
}

int main(int argc, char * argv[])
{
  signal(SIGALRM,handler); //register handler to handle SIGALRM
  alarm(1); //Schedule a SIGALRM for 1 second
  while(1) {
    printf("Turing was right!\n");
    sleep(15); //sleep for 15 seconds until which the signal handler will interrupt and exit the process
  } //busy wait for signal to be delivered
  return 0; //never reached
}