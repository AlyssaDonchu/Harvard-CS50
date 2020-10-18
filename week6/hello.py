import cs50

class Solution:
    def mario():
        height = cs50.get_int("Please, enter a number bettween 1 and 8: ")
        if height < 1 or height > 8: #we check if the number between 1 to 8, if not, we use recursion to initialize the function again
            Solution.mario()
        Solution.print_pyramid(height) #we send the integer into print_pyramid function
    
    def print_pyramid(int):
        i = 1
        i2 = int - 2
        while i < int:
            print(" "*i2,"#"*i,"","#"*i)
            i += 1
            i2 -= 1
        print("#"*i,"","#"*i) #prints the last part of the pyramid with no spaces at the beginning

Solution.mario()
