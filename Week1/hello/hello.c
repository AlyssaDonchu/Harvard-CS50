#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Variable with the type string that asks for user's name
    string name = get_string("What's your name?\n");
    //function from standard input output library that prints "hello" and the name of the user
    printf("hello, %s\n", name);
}
