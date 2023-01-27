#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)


    pair locked_pairs[pair_count]; // this is a dummy array to keep track of the locked pairs. an efficient solution will not require the use of this array.

    for (int i = 0; i < pair_count; i++)
    {
        locked_pairs[i].winner = 99;
        locked_pairs[i].loser = 99;
    }

    int count = 0;
    bool cycle = false;
    int cycle_count = 0;
    int loser;
    int winner;
    int target;

    for (int i = 0; i < pair_count; i++) // the i pair will be the pair being considered
    {
        cycle = false;  // setting this back to false if it was triggered to true on the last iteration

        for (int j = 0; j < pair_count; j++) // the j pair is the one being referenced against
        {
            if (pairs[i].loser == locked_pairs[j].winner)   // this is the first test for a cycle; if this test is satisfied, the pair COULD cause a cycle, but also may not.
            {
                winner = locked_pairs[j].winner;
                loser = locked_pairs[j].loser;
                target = pairs[i].winner;
                for (int k = 0; k < pair_count; k++)    // Here we need to investigate the locked pairs to see if a path back to the winner of the considered pair exists. If it does, the pair is discarded.
                {
                    if (locked_pairs[k].loser == target)
                    {
                        break;
                    }
                    else if (loser == locked_pairs[k].winner)
                        {
                        winner = locked_pairs[k].winner;
                        loser = locked_pairs[k].loser;
                        k = -1; //RESTARTS LOOP TO CHECK THE NEXT CONDITION!
                        }
                }
            }
            else
            {
                continue;
            }
        }
        if (cycle == true)
        {
            continue;
        }
        else
        {
                locked_pairs[count] = pairs[i];  // if not, then go ahead and add that pair.
                locked[pairs[i].winner][pairs[i].loser] = true;
                count++;
        }
    }
    if (cycle_count != 0)
    {
        for (int m = 0; m < pair_count; m++)
            {
                locked[pairs[m].winner][pairs[m].loser] = true;
            }

    }
    return;



// {

//     pair locked_pairs[pair_count]; // this is a dummy array to keep track of the locked pairs. an efficient solution will not require the use of this array.

//     for (int i = 0; i < pair_count; i++)
//     {
//         locked_pairs[i].winner = 99;
//         locked_pairs[i].loser = 99;
//     }

//     int count = 0;
//     bool cycle = false;
//     int cycle_count = 0;
//     int loser;
//     int winner;
//     int target;

//     for (int i = 0; i < pair_count; i++) // the i pair will be the pair being considered
//     {
//         cycle = false;  // setting this back to false if it was triggered to true on the last iteration

//         for (int j = 0; j < pair_count; j++) // the j pair is the one being referenced against
//         {
//             if (pairs[i].loser == locked_pairs[j].winner)   // this is the first test for a cycle; if this test is satisfied, the pair COULD cause a cycle, but also may not.
//             {
//                 winner = locked_pairs[j].winner;
//                 loser = locked_pairs[j].loser;
//                 target = pairs[i].winner;

//                 for (int k = 0; k < pair_count; k++)    // Here we need to investigate the locked pairs to see if a path back to the winner of the considered pair exists. If it does, the pair is discarded.
//                 {
//                     if (locked_pairs[k].loser == target)
//                     {
//                         cycle = true;
//                         cycle_count++;
//                         break;
//                     }
//                     else if (loser == locked_pairs[k].winner)
//                         {
//                         winner = locked_pairs[k].winner;
//                         loser = locked_pairs[k].loser;
//                         k = -1; //RESTARTS LOOP TO CHECK THE NEXT CONDITION!
//                         }
//                     }
//             }
//             else
//             {
//                 continue;
//             }
//         }
//         if (cycle == true)
//         {
//             continue;
//         }
//         else
//         {
//                 locked_pairs[count] = pairs[i];  // if not, then go ahead and add that pair.
//                 locked[pairs[i].winner][pairs[i].loser] = true;
//                 count++;
//         }
//     }
//     if (cycle_count == 0)
//     {
//         for (int i = 0; i < pair_count; i++)
//         {
//             locked[pairs[i].winner][pairs[i].loser] = true;
//         }
//     }
// }

    // int candidate[] = {72, 91, 54, 61, 37, 88, 13, 20};
    // int triggers[] = {13, 45, 63, 88, 41, 91, 50, 22};
    // int candidate_count = 8;
    // int matches[8];
    // int locked[candidate_count];
    // int count = 0;

    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for(int j = 0; j < candidate_count; j++)
    //     {
    //         if (candidate[i] == triggers[j])
    //         {
    //             matches[count] = candidate[i];
    //             count++;
    //         }

    //     }

    // }
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     printf("%i\n", matches[i]);
    // }



    // int test[] = {1, 1, 1, 1, 1, 4, 1, 1};
    // bool same_values;

    // for (int i = 1; i < 8; i++)
    // {
    //     if (test[0] == test[i])
    //     {
    //         same_values = true;
    //     }
    //     else
    //     {
    //         same_values = false;
    //         printf("Not all values are the same.\n");
    //         break;
    //     }
    // }

    // if (same_values == true)
    // {
    //     printf("All values are the same.\n");



    // int test[] = {6, 3, 8, 5, 2, 7, 4, 1};

    // int replacement;
    // int position;

    // for (int i = 0; i < 8; i++)
    // {
    //     int selection = test[i];
    //     for (int j = i; j < 8; j++)
    //     {
    //         if (test[j] > selection)
    //         {
    //             selection = test[j];
    //             position = j;
    //         }
    //     }
    // if (test[i] == selection)
    // {

    // }
    // else
    // {
    //     replacement = test[i];
    //     test[i] = selection;
    //     test[position] = replacement;
    // }

    // }
    // for (int i = 0; i < 8; i++)
    // {
    //     printf("%i ", test[i]);

    // }
// }

    // int test_array[] = {1, 2, 3, 4, 5, 6, 7, 8};

    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = i; j < 8; j++)
    //     {
    //     printf("%i", test_array[j]);
    //     }
    //     printf("\n");
    // }


// for (int i = 0; i < candidate_count; i++)
//     {
//         bool result = false;
//         if (locked[loser][i] == true)
//         {
//             result = check_circular(i, winner);
//         }
//         if (result == true || i == candidate_count - 1) // Only return result if all branches checked or the last checked branch showed circularity
//         {
//             return result;
//         }
//     }

// Function that follows the path of winners and losers to establish if there is a cycle.
int cyclecheck (int winner, int loser, int seed)
{
    for (int i = 0; i < pair_count; i++)
    {
        // the loser is the seed, a cycle is created
        if (locked[loser][i] == true && seed == i)
        return 0;  // the return zero exits the whole program which causes problems wrt checking if other cycles exist.

        // the loser matches a winner in the locked set, but there are more cases to check
        else if (locked[loser][i] == true)
        return cyclecheck (loser, i, seed);
    }
return 1;
}

// Function that follows the path of winners and losers to establish if there is a cycle.
int cyclecheck (int winner, int loser, int seed)
{
    int potential_cycle[pair_count];
    int true_count = 0;

    for (int i = 0; i < pair_count; i++)
    {
        true_count = 0;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[loser][j] == true)
            {
                potential_cycle[true_count] = j;
                true_count++;
            }
        }

        // the loser is the seed, a cycle is created
        if (locked[loser][i] == true && seed == i)
        return 0;  // the return zero exits the whole program which causes problems wrt checking if other cycles exist.

        // the loser matches a winner in the locked set, but there are more cases to check
        else if (locked[loser][i] == true && true_count == 1)
        return cyclecheck (loser, i, seed);

        else if (locked[loser][i] == true && true_count > 1)
        {
            for (int k = 0; k < pair_count; k++)
                {
                    for (int m = 0; m < true_count; m++)
                    {
                         if (locked[potential_cycle[k]][m] == true && m == seed)
                         return 0;

                         else if (locked[potential_cycle[k]][m] == true)
                         {
                            winner = locked_pairs[k].winner;
                            loser = locked_pairs[k].loser;
                            m = -1; //RESTARTS LOOP TO CHECK THE NEXT CONDITION!
                         }





                        //  else if (locked[potential_cycle[k]][m] == true)
                        //  return cyclecheck (m, i, seed);
                    }
                }
        }
    }
return 1;
}



bool cyclecheck (int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true && cyclecheck(winner, i))
        {
            return true;
        }
    }
    return false;
}