// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2]; //every person has an array of two parents. Each parent is a pointer to another person.
    char alleles[2]; //representing which alleles; A, B, or O
}
person;

const int GENERATIONS = 3;  //the number of generations of data that we are simulating generating. child, parents, grandparents.
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)  //do not need to change anything here
{
    // Seed random number generator; randomly choose which gene is passed on
    srand(time(0));

    // Create a new family with three generations; returns a pointer to the most recent generation of person in the family
    // A family with three generation will result in a pointer to a person, then we can follow that persons parent pointer to their parents, and the parents pointer to the grandparents.
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    // This has already been written
    print_family(p, 0);

    // Free memory
    // This needs to be written
    free_family(p);
}

/*
    TODO:
    Complete the create_family function to create a family with a specified number fo generations.
        Allocate memory for a new person using malloc. Calling malloc, passing in sizeof(person).
        Use this person to generate more ancestors if there are more generations that you need to work with.
            If generations > 1, recursively create the previous generations.
                Using the return value you get from the create_family functions, you'll update that persons parents.
                After parent pointers are set, inherit one allele from each parent at random. Look at one parents set of alleles, choose one at random and assign that person[0] allele[0], then look at the other parent's alleles, randomly choose one and assign it as person[0] allele[1].
            If generations == 1 (grandparents), set the parents to NULL, and randomly generate the alleles for the grandparents (use the function given to randomly generate the alleles)

    We need to free all the memory for each instance of malloc that we called.
        Base case: handle an input of NULL. No action should be taken.
        Recursive case: recursively free the parents, then free the child.
            Call the free family function on each of the child's two parents.
                Recursively then, that will free the parents of the parents, and any further generations thereof.

    $ ./inheritance
    Child (Generation 0): blood type OO
        Parent (Generation 1): blood type AO
            Grandparent (Generation 2): blood type OA
            Grandparent (Generation 2): blood type BO
        Parent (Generation 1): blood type OB
            Grandparent (Generation 2): blood type AO
            Grandparent (Generation 2): blood type BO
 */

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    //n is a temporary variable. allocating the size of a person which has enough memory to store two alleles and two pointers (parents) variables.
    person *p = malloc(sizeof(person));

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // TODO: Set parent pointers for current person
        p->parents[0] = parent0;
        p->parents[1] = parent1;

        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];

    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // TODO: Randomly assign alleles
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    return p;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{

    // TODO: Handle base case
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
