#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

float readability_calc(char *str)
{
    // l is the average number of letters per 100 words in the text
    // s is the average number of sentences per 100 words in the text
    float l; 
    float s;
    float formula;
    int i = 0;
    float letters = 0;
    float words = 0;
    float sentences = 0;
    //checks how many words we have in the string
    while (i < strlen(str))
    {
        //checks if each char in the string is between "a" to "z" and "A" to "Z" (ascii decimal 
        //representation of the letters)
        if ((str[i] >= 97 && str[i] <= 122) || (str[i] >= 65 && str[i] <= 90))
        {
            letters++;
        }
        i++;
    }
    //checks how many sentences we have in the string
    i = 0;
    while (i <= strlen(str))
    {
        //check if each char is spase,backspace, tab, new line (ascii decimal representation of \t, \b
        //and \n) or the end of the string ("\0")
        if ((str[i] >= 8 && str[i] <= 10) || (str[i] == 32) || (str[i] == '\0'))
        {
            words++;
        }
        i++;
    }
    i = 0;
    while (i < strlen(str))
    {
        //checks for periods, exclamation points, or question marks and counts them as a sentence
        if (str[i] == 33 || str[i] == 46 || str[i] == 63)
        {
            sentences++;
        }
        i++;
    }
    l = (letters / words) * 100;
    s = (sentences / words) * 100;
    formula = 0.0588 * l - 0.296 * s - 15.8;
    return (formula);
    
}

int main(void)
{
    char *str = get_string("Please, enter your test:\n");
    float grade = readability_calc(str);
    // rounds the float number with a builtin roundf function
    int round_num = roundf(grade);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return (0);
    }
    if (grade >= 16)
    {
        printf("Grade 16+\n");
        return (0);
    }
    else
    {
        printf("%s %d\n", "Grade", round_num);
        return (0);
    }
}
