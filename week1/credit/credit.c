#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


//Function the check the length
int get_len(long nbr)
{
    long len = 0;
    if (nbr <= 0)
    {
        ++len;
    }
    while (nbr != 0)
    {
        ++len;
        nbr = nbr / 10;
    }
    return (len);
}

//This function flips an integer into a string
char    *ft_itoa(long nbr)
{
    char *result;
    long len;

    //checks the length of the integer
    len = get_len(nbr);
    //reserves memory with built-in "malloc" function + 1 byte for the last "/0" in the new string
    result = malloc(sizeof(char) * (len + 1));
    result[len] = '\0';
    
    //goes throuth the "result" from the end, takes each char and makes it equal to the credit card number
    // % (modulo) 10 and + '0' (means ascii value, 48 or '0', so the program will know from what character
    // in the ascii table it should count)
    while (nbr != 0)
    {
        --len;
        result[len] = (nbr % 10) + '0';
        nbr = nbr / 10;
    }
    return (result);
}

int     valid_or_invalid(int i, int credit_len, char *str)
//in this funtion we have 2 indexes, 1 for multiplication of every other number,
//the other one is to add to the sum the digits that weren’t multiplied by 2
{
    int multiplication = 0;
    int i2;
    if (i == 1)
    {
        i2 = 0;
    }
    if (i == 0)
    {
        i2 = 1;
    }
    int number = 0;
    while (i < credit_len)
    {
        number = str[i] - '0';
        if (number * 2 >= 10)
        {
            int temp_number = number * 2;
            char *temp_str = ft_itoa(temp_number);
            int temp_index = 0;
            int temp_len = get_len(temp_number);
            while (temp_index < temp_len)
            {
                int temp_number2 = 0;
                temp_number2 = temp_str[temp_index] - '0';
                multiplication += temp_number2;
                temp_index++;
            }
        }
        else
        {
            multiplication += number * 2;
        }
        i += 2;
    }
    //Adding to the sum digits that weren't multiplied by 2
    while (i2 < credit_len)
    {
        number = str[i2] - '0';
        multiplication += number;
        i2 += 2;
    }
    return (multiplication);
}

int main(void)
{
    //The program starts here - asking the user to enter a credit card number and check the length 
    long credit_num = get_long("Please, enter a credit card number:\n");
    int credit_len = get_len(credit_num);
    if (credit_len < 13 | credit_len > 16)
    {
        printf("INVALID\n");
        return (0);
    }
    //change the type from integer to string through itoa function
    char *string_credit = ft_itoa(credit_num);
    int i = 0;
    //valid_or_invalid function will check the algorithm invented by Hans Peter Luhn of IBM
    //meaning, will multiply every other digit 2, 
    //Add the sum to the sum of the digits that weren’t multiplied by 2
    //and checks if the total’s last digit is 0
    int multiplication = valid_or_invalid(i, credit_len, string_credit);
    int len_multiplication = get_len(multiplication);
    char *string_multiplication = ft_itoa(multiplication);
    //We should check every other number, so first time we check from index 0 and second time from index 1
    if (string_multiplication[len_multiplication - 1] != '0')
    {
        i = 1;
        multiplication = valid_or_invalid(i, credit_len, string_credit);
        string_multiplication = ft_itoa(multiplication);
    }
    if (string_multiplication[len_multiplication - 1] == '0')
    {
        //All American Express numbers start with 34 or 37
        if (string_credit[0] == '3' && string_credit[1] == '4' | string_credit[1] == '7')
        {
            printf("AMEX\n");
            return (0);
        }
        //most MasterCard numbers start with 51, 52, 53, 54, or 55
        if (string_credit[0] == '5' && string_credit[1] >= '1' && string_credit[1] <= '5')
        {
            printf("MASTERCARD\n");
            return (0);
        }
        //all Visa numbers start with 4
        if (string_credit[0] == '4')
        {
            printf("VISA\n");
            return (0);
        }
    }
    else
    {
        printf("INVALID\n");
        return (0);
    }
    printf("INVALID\n");
    return (0);
}
