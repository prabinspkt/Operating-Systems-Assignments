#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int sub (int a, int b);
int mul (int a, int b);
int division (int a, int b);
void quit();


int main (void)
{
  int a = 10;
  int b = 23;
  printf("Predefined number 'a' is %d\n", a);
  printf("Predefined number 'b' is %d\n", b);
  printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit): 0\n");
  char user_option = getchar();
  int int_option = user_option - '0';
  
  for (int i = int_option; int_option <= 0; i++) {
    int x = add(a,b);
    printf("The result is %d.\n", x);
    exit(0);
    }
  for (int i = int_option; int_option <= 1; i++) {
    int x = sub(a,b);
    printf("The result is %d.\n", x);
    exit(0);
  }
  for (int i = int_option; int_option <= 2; i++) {
    int x = mul(a,b);
    printf("The result is %d.\n", x);
    exit(0);
  }
  for (int i = int_option; int_option <= 3; i++) {
    int x = division(a,b);
    printf("The result is %d.\n", x);
    exit(0);
  }
  for (int i = int_option; int_option <= 4; i++) { quit(); }

	return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { printf ("Adding 'a' and 'b'\n"); return a + b; }
int sub (int a, int b) { printf ("Subtracting 'a' and 'b'\n"); return a - b; }
int mul (int a, int b) { printf ("Multiplying 'a' and 'b'\n"); return a * b; }
int division (int a, int b) { printf ("Dividing 'a' and 'b'\n"); return a / b; }
void quit() { exit(0); }
