#include <stdio.h>
#include <cs50.h>

int test;
int collatz(int n);
int additional(int m);


int main(void)
{
    test = get_int("Please input the number for the collatz conjecture.\n");
    printf("%i\n", collatz(test));
}

int collatz(int n)
{
    //base case
    if (n == 1)
        return 0;
    // even numbers
    else if ((n % 2) == 0)
        return 1 + collatz(n/2);
    // odd numbers
    else
        return 1 + collatz(3*n + 1);
}
