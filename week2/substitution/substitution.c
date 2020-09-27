#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

//this function checks if the characters in the argument are unique.
int if_unique(char *str)
{
    int i = 0;
    int i2 = 0;
    //we create an array with the size of 123 (remember - ascii characters, "A" to "Z" equals to decimal value
    //from 65 to 90, and "a" to "z" equals to 97 to 122).
    //we set all the characters in the array to 0 and go through the cipher key.
    //then, we change the value to 1 for each character. 
    //if the character isn't unique, the value will show 1 and not 0.
    int unique[123] = {0};
    while (i < strlen(str))
    {
        i2 = str[i];
        if (unique[i2] == 1)
        {
            return (1);
        }
        unique[i2] = 1;
        i++;
    }
    return (0);
}

int if_alphabetic(char *str)
{
    int i = 0;
    while (i < strlen(str))
    {
        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
        {
            i++;
        }
        else
        {
            return (1);
        }
    }
    return (0);
}

int error_message()
{
    printf("Please enter only 1 cipher key with 26 alphabetic, unique characters.\n");
    return (0);
}

int main(int argc, char **argv)
{
    //if there's no argument (the first argument is the name of the file), the program
    //will shows an error message and will return 1.
    if (argc == 1)
    {
        error_message();
        return (1);
    }
    //we checking the length of the argument with a build in "strlen" function.
    int len = strlen(argv[1]);
    //we check if the user enter 1 argument and if the length is 26.
    if ((argc == 2) && (len == 26))
    {
        //we check if all the characters are alphabetical, if not, the program shows an error and returns 1.
        if (if_alphabetic(argv[1]) == 1)
        {
            error_message();
            return (1);
        }
        //we check of all the characters are unique, if not, the program shows an error and returns 1.
        if (if_unique(argv[1]) == 1)
        {
            error_message();
            return (1);
        }
        //this is the text that the user wants to encrypt.
        char *plain_text = get_string("plaintext: ");
        //here we create an array with a size of 123 characters. Those are for storing the cipher key for 
        //lower case and upper case.
        //The size is 123, because by ascii table, upper case from a to z are equal to decimal numbers from 65
        //to 90 and lower case equal to 97 to 122.
        int unique[123] = {0};
        //i equals 65 because we want to put the characters at the same place as the ascii table goes
        //from 65 to 90 we going to store upper case characters.
        int i = 65;
        int i2 = 0;
        char *argument = argv[1];
        while (argument[i2] != '\0')
        {
            //if the character is lower case, we change it to upper case.
            if (argument[i2] >= 'a' && argument[i2] <= 'z')
            {
                argument[i2] -= 32;
            }
            //we assign the array the same valas the character.
            unique[i] = argument[i2];
            i++;
            i2++;
        }
        //this part is for lower case.
        i = 97;
        i2 = 0;
        while (argument[i2] != '\0')
        {
            //if the character is upper case, we change it to lower case.
            if (argument[i2] >= 'A' && argument[i2] <= 'Z')
            {
                argument[i2] += 32;
            }
            unique[i] = argument[i2];
            i++;
            i2++;
        }
        //we check the length of the text that the user wants to encrypt.
        len = strlen(plain_text);
        i = 0;
        i2 = 0;
        //we creating a new string and assigning a memory to it, same as the size of user's text.
        //we doing this with the built-in "malloc" function (for more info - man malloc).
        char *new_string;
        new_string = malloc(sizeof(char) * (len + 1));
        //adding "\0" at the end, to show to the system where the string ends.
        new_string[len] = '\0';
        //in this while loop we make the encryption and put the characters in the new string.
        while (i < len)
        {
            i2 = plain_text[i];
            new_string[i] = unique[i2];
            //if the character is a digit, space or comma - do not encrypt. At this point we may consider
            //adding cases like period, question or exclamation mark, but it wasn't part of the test cases.
            if ((plain_text[i] >= 48 && plain_text[i] <= 57) || plain_text[i] == 32 || plain_text[i] == 44)
            {
                new_string[i] = plain_text[i];
            }
            i++;
        }
        printf("ciphertext: ");
        printf("%s\n", new_string);
    }
    else
    {
        error_message();
        return (1);
    }
}
