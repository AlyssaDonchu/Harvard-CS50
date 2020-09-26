#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int width = get_int("How tall is the piramide?\n") + 1;
    int count_spaces = width;
    int count1 = 1;
    int count2 = 1;
    //Checks of the original user input (width) is between 1 and 8
    if (width > 1 && width <= 9)
    {
        //counting the height of the piramide
        while (count1 != width)
        {
            //counting and printing spaces first
            count_spaces = width - count1;
            while (count_spaces != 1)
            {
                printf(" ");
                count_spaces--;
            }
            //counting and printing "#""
            while (count2 != 0)
            {
                printf("#");
                count2--;
            }
            //printing a separator of 2 spaces
            printf("  ");
            count2 = count1;
            //counting and printing "#", again
            while (count2 != 0)
            {
                printf("#");
                count2--;
            }
            //printing a new line and adding +1 to the variable "count1"
            printf("\n");
            count1++;
            count2 = count1;
        }
    }
    //if user's input is not between 1 and 8, run the program again, until this little prick will put the correct number. 
    else
    {
        main();
    }
}
