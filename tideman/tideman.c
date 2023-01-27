#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cyclecheck(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i == j)
            {

            }
            else
            {
                //Go to the i candidates row and increment the j candidates
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = j + 1; i < candidate_count; i++)
        {
            int A = preferences[j][i];
            int B = preferences[i][j];

            if (A > B)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            else if (A < B)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (A == B)
            {

            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength[candidate_count];
    int sort_counter = 0;

    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = j + 1; i < candidate_count; i++)
        {
            int A = preferences[j][i];
            int B = preferences[i][j];
            //at this point I don't even remember writing this function. it finds the strength of the victories

            if (A > B)
            {
                strength[sort_counter] = A - B;
                sort_counter++;
            }
            else if (A < B)
            {
                strength[sort_counter] = B - A;
                sort_counter++;
            }
            else if (A == B)
            {
                strength[sort_counter] = A - B;
                sort_counter++;
            }
        }
    }

    int replacement;
    int position;
    int hold_winner;
    int hold_loser;

    for (int i = 0; i < candidate_count; i++)
    {
        int selection = strength[i];
        for (int j = i; j < candidate_count; j++)
        {
            if (strength[j] > selection)
            {
                selection = strength[j];
                position = j; // This was the position where the highest value was found
            }
        }
        if (strength[i] == selection)
        {

        }
        else
        {
            // this was written in one go, pretty cool
            replacement = strength[i];
            strength[i] = selection;
            strength[position] = replacement;
            hold_winner = pairs[i].winner;
            hold_loser = pairs[i].loser;
            pairs[i] = pairs[position];
            pairs[position].winner = hold_winner;
            pairs[position].loser = hold_loser;
        }
    }
    return;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (!cyclecheck(winner, loser)) //if cyclecheck is false then lock the pair as true
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int true_count;
    for (int i = 0; i < pair_count; i++)
    {
        true_count = 0;
        for (int j = 0; j < pair_count; j++)    //combination of for loops that loops at which column is the empty one
        {
            if (locked[j][i] == true)
            {
                true_count++;
            }

            if (j == pair_count - 1 && true_count == 0)
            {
                printf("%s\n", candidates[i]);
                // the i value is used as an index reference to the candidates array. The name of that candidate is printed
            }
        }
    }
    return;

}

bool cyclecheck(int winner, int loser)
{
    if (locked[loser][winner] == true)  //recursive boolean functions always have to begin with checking if a value should be returned
    {
        return true;
    }

    for (int i = 0; i < pair_count; i++)
    {
        if (locked[loser][i] == true && cyclecheck(winner, i))
            //leverages idea that for a winner loser pair, there cannot be a loser winner pair. if one is detected a cycle is created.
        {
            return true;
        }
    }
    return false;
}