import cs50

class Solution:
    def readability():
        string = cs50.get_string("Please, enter your text: ")
        letters = 0
        words = 0
        sentences = 0
        #in this for loop we count the number of words, letters and sentences
        for i in string:
            if i.isalpha():
                letters += 1
            if i == " ":
                words += 1
            if i == "." or i == "!" or i == "?":
                sentences += 1
        #at the end I increased the word by one, because in C language we had the option to recognize the end if
        #string by "\0", here we count the words by " " (space) separator and that way it doesn't count the last word,
        #so we add it manually by increasing the word by one
        words += 1
        #the Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8, where L is the average number of
        #letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
        l = letters / words * 100
        s = sentences / words * 100
        grade = round(0.0588 * l - 0.296 * s - 15.8)
        
        if grade < 1:
            print("Before Grade 1")
            return(0)
        if grade >= 16:
            print("Grade 16+")
            return(0)
        else:
            print("Grade", grade)
            return(0)

Solution.readability()
