import cs50
#in this solution we change the type of the credit card number from int to str and vice versa to manipulate the string
class Solution:
    def your_credit():
        credit_num = cs50.get_int("Please,enter your credit card number: ")
        #we changing the type to string and sending it to the calculation function
        string = str(credit_num)
        if (Solution.calculation(string, i = 0)) == True or (Solution.calculation(string, i = 1)) == True:
            if string[0:2] == "34" or string[0:2] == "37":
                print("AMEX")
            if string[0:2] >= "51" and string[0:2] <= "55":
                print("MASTERCARD")
            if string[0] == "4":
                print("VISA")
        else:
            print("INVALID")
            
    def calculation(string, i):
        length = len(string)
        if length < 13 or length > 16:
            print("INVALID")
            return(0)
        lst_other_digit = []
        temp_int2 = 0
        sum_num = 0
        #we have 2 different indexes to multiply every other number, once it multiplies from index 0 and once from index 1
        if i == 0:
            i2 = 1
        if i == 1:
            i2 = 0
        #in this while loop we multiply every other number by 2 and add it to the list
        while i < length:
            temp_int = int(string[i])
            temp_int *= 2
            lst_other_digit.append(temp_int)
            i += 2
        #here we add together all the numbers (those that were multiplied and those that did not)
        for i in lst_other_digit:
            #if the number is 10 or greater than 10, we need to "break" into digits and add them together
            if i >= 10:
                temp_int = int(i/10)
                temp_int2 = i % 10
                i = temp_int + temp_int2
            sum_num += i
        while i2 < len(string):
            temp_int = int(string[i2])
            sum_num += temp_int
            i2 += 2
        #if the last digit of sum_num is 0, the card is Valid and we'll return true. 
        if str(sum_num)[-1] == "0":
            return(True)
        else:
            return(False)
              

    
Solution.your_credit()
