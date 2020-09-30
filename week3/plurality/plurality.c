#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

// Update vote totals given a new vote
bool vote(string name)
{
    int i = 0;
    while (i < candidate_count)
    {
        //Compares between 2 strings, if they are the same, adds +1 to the votes and returns true.
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
        i++;
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int i = 0;
    //New variable to store the maximum number of votes.
    int max_votes = 0;
    //In this while loop we look for the highest number of votes and store the number inside the variable "max_votes".
    while (i < candidate_count)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
        i++;
    }
    //Setting i to 0 and go through the votes again, to check if we have the same max_votes for more than 1 candidate. 
    i = 0;
    while (i < candidate_count)
    {
        if (max_votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
        i++;
    }
}

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (vote(name) == false)
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}
