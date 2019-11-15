/*------------------------------------------------------*/
/* Skeleton for the synchronization Lab .   assignment 	*/
/*------------------------------------------------------*/
/* Note:						                        */
/* -----						                        */
/* 1. E = Elephant					                    */
/* 2. D = Dog						                    */
/* 3. C = Cat					                    	*/
/* 4. M = Mouse						                    */
/* 5. P = Parrot					                    */
/*------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define  CHILD		0       /* Return value of child proc from fork call */

int main()
{
    // Declare all semaphores to be used
    sem_t * elephant_or_mice;
    sem_t * dog_or_cat;
    sem_t * cat_or_parrot;
    sem_t * parrot_or_mice;
    
    int pid;		/* Process id after fork call */
    int i;		/* Loop index. */
    int N;		/* Number of requests to process */
    int status;  	/* Exit status of child process. */
    int type;           /* Type of animal */
    int *zoo_spots_ptr;
    int fd;
    int zero = 0;
    int * counter_ptr;
  
    //open a file and map it into memory this is to hold the shared counter
    fd = open("zoo_log.txt",O_RDWR|O_CREAT,S_IRWXU);
    write(fd,&zero,sizeof(int));
    counter_ptr = mmap(NULL,sizeof(int),PROT_READ |PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);

    /* create, initialize semaphore */
    // Create one semaphore for two animals that cannot access the cage at the same time
    // So, both animals will use the same semaphore for accessing which ensures mutual exclusion
    if ((elephant_or_mice = sem_open("elephant_or_mice_sem", O_CREAT, 0644, 1)) == SEM_FAILED) {
        perror(" elephant_or_mice_sem initilization");
        exit(1);
    }
    if ((dog_or_cat = sem_open("dog_or_cat_sem", O_CREAT, 0644, 1)) == SEM_FAILED) {
        perror(" dog_or_cat_sem initilization");
        exit(1);
      }
    if ((cat_or_parrot = sem_open("cat_or_parrot_sem", O_CREAT, 0644, 1)) == SEM_FAILED) {
        perror(" cat_or_parrot_sem initilization");
        exit(1);
      }
    if ((parrot_or_mice = sem_open("parrot_or_mice_sem", O_CREAT, 0644, 1)) == SEM_FAILED) {
        perror(" parrot_or_mice_sem initilization");
        exit(1);
      }
     
    printf("How many requests to be processed: \n");
    scanf("%d",&N);

    for (i=1; i<=N; i++) {
        printf("Who wants in (E=1)(D=2)(C=3)(M=4)(P=5): \n");
        fflush(stdout);
        scanf("%d",&type);
        if ((pid = fork()) == -1) {
   	        /* Fork failed! */
	        perror("fork");
	        exit(1);
        }
        
        
        if (pid == CHILD) {
	        pid = getpid();
            switch (type) {

              case 1: /* Elephant code*/
                          printf("     Elephant process with pid %d wants in.\n",pid);
                          fflush(stdout);
                          sem_wait(elephant_or_mice);
                          printf("     Elephant process with pid %d is in.\n",pid);
                          fflush(stdout);
                          sleep(rand()%10);
                          sem_post(elephant_or_mice);
                          printf("     Elephant process with pid %d is out.\n",pid);
                          fflush(stdout); 
                          break;

              case 2:  /*Dog code*/
                          printf("     Dog process with pid %d wants in.\n",pid);
                          fflush(stdout);
                          sem_wait(dog_or_cat);
                          printf("     Dog process with pid %d is in.\n",pid);
                          fflush(stdout);
                          sleep(rand()%10);
                          sem_post(dog_or_cat);
                          printf("     Dog process with pid %d is out.\n",pid);
                          fflush(stdout);
                      break;

              case 3: /*Cat Code*/
                          printf("     Cat process with pid %d wants in.\n",pid);
                          fflush(stdout);
                          sem_wait(dog_or_cat);
                          printf("     Cat process with pid %d is in.\n",pid);
                          fflush(stdout);
                          sleep(rand()%10);
                          sem_post(dog_or_cat);
                          printf("     Cat process with pid %d is out.\n",pid);
                          fflush(stdout);
                      break;

              case 4: /*Mouse code*/
                          printf("     Mouse process with pid %d wants in.\n",pid);
                          fflush(stdout);
                          sem_wait(elephant_or_mice);
                          printf("     Mouse process with pid %d is in.\n",pid);
                          fflush(stdout);
                          sleep(rand()%10);
                          sem_post(elephant_or_mice);
                          printf("     Mouse process with pid %d is out.\n",pid);
                          fflush(stdout); 
                      break;

              case 5: /*Parrot  Code*/
                          printf("     Parrot process with pid %d wants in.\n",pid);
                          fflush(stdout);
                          sem_wait(parrot_or_mice);
                          printf("     Parrot process with pid %d is in.\n",pid);
                          fflush(stdout);
                          sleep(rand()%10);
                          sem_post(parrot_or_mice);
                          printf("     Parrot process with pid %d is out.\n",pid);
                          fflush(stdout);
                      break;
            }
            exit(0);
        }
    }
    
    /* Now wait for the child processes to finish */
    for (i=1; i<=N; i++) {
        pid = wait(&status);
        printf("Child (pid = %d) exited with status %d.\n", pid, status);
        fflush(stdout);
    }
}


