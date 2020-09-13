#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Variable with the type string that asks for users name
    string name = get_string("What's your name?\n");
    //function from standart input output library that prints "hello" and the name of the user
    printf("hello, %s\n", name);
}
