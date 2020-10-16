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
    int i = 0;
    while (i < candidate_count)
    {
        //Here we compare between 2 strings to check if the "name" exists in the candidate list 
        if (strcmp(candidates[i], name) == 0)
        {
            //if the name exists, we find his index
            ranks[rank] = i;
            return true;
        }
        i++;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int i = 0;
    while (i < candidate_count)
    {
        //j equals i + 1, because we want to the number that's "after"
        int j = i + 1;
        while (j < candidate_count)
        {
            //we capture the preferences in a 2 dimensional array
            int candidate_i = ranks[i];
            int candidate_j = ranks[j];
            preferences[candidate_i][candidate_j]++;
            j++;
        }
        i++;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

int comparator(const void *a, const void *b)
{
    pair *orderA = (pair *)a;
    pair *orderB = (pair *)b;

    return (preferences[orderB->winner][orderB->loser] - preferences[orderA->winner][orderA->loser]);
}

//decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.
void sort_pairs(void)
{
    pair temp;
    for (int i = 1; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i; j++)
        {
            if (pairs[j].loser < pairs[j + 1].loser)
            {
                temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

bool makes_circle(int cycle_start, int loser)
{
    if (loser == cycle_start)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (makes_circle(cycle_start, i))
            {
                return true;
            }
        }
    }
    return false;
}

//Locking the pairs
void lock_pairs()
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!makes_circle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

//prints out the name of the candidate who is the source of the graph
void print_winner(void)
{
    int winner;
    int rank;

    for (int i = 0; i < candidate_count; i++)
    {
        rank = 0;
        for (int k = 0; k < candidate_count; k++)
        {
            if (locked[k][i] == false)
            {
                rank++;
            }
        }
        if (rank == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
}
