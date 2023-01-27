#include <cs50.h>
#include <stdio.h>

int get_cents(void);

int main(void)
    {
    // Ask how many cents the customer is owed
    int cents = get_cents();
    }
int get_cents(void)
{
    int n;
    do
    {
        n = get_int("Change owed: ");
    }
    while (n < 0);
    return n;
}