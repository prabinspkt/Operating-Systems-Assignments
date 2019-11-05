// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
    // We a single two way pipe
  
    int fd1[2];  // Used to store two ends of the pipe 
  
    char fixed_str_one[] = "howard.edu"; 
		char fixed_str_two[] = "gobison.org";
    char input_str[100]; 
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    }
  
    printf("Enter a string to concatenate:");
    scanf("%s", input_str); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
        char concat_str[100]; 
  
        // Write input string and close writing end of first 
        // pipe. 
        write(fd1[1], input_str, strlen(input_str)+1); 
  
        // Wait for child to send a string 
        wait(NULL); 
  
        // Read string from child, print it and close 
        // reading end. 
        read(fd1[0], concat_str, 100); 
				int k = strlen(concat_str);
				int i;
				for (i=0; i<strlen(fixed_str_two); i++)
					concat_str[k++] = fixed_str_two[i];
			
				concat_str[k] = '\0';   // string ends with '\0'
			
        printf("Concatenated string in P1 %s\n", concat_str);
			
        close(fd1[0]); 
    } 
  
    // child process 
    else
    {  
        // Read a string using first pipe 
        char concat_str[100]; 
        read(fd1[0], concat_str, 100); 
  
        // Concatenate a fixed string with it 
        int k = strlen(concat_str); 
        int i; 
        for (i=0; i<strlen(fixed_str_one); i++) 
            concat_str[k++] = fixed_str_one[i]; 
			
				concat_str[k] = '\0';   // string ends with '\0'
				printf("Concatenated string in P2 %s\n", concat_str);
			
        // Write concatenated string and close writing end 
        write(fd1[1], concat_str, strlen(concat_str)+1); 
        close(fd1[1]); 
  
        exit(0); 
    } 
} 