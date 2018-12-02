"""
This script contains demonstration of the string and list slice operator
"""


# Take input and print every other character
def display_alternate(input_str: any):
    print("Input : " + str(input_str))

    print("0 : " + str(input_str[::2]))
    print("1 : " + str(input_str[1::2]))


input_str = "My cat runs and plays"
display_alternate(input_str)

input_str = [2, 4, 6, 8, 10, 12, 14, 16, 18]
display_alternate(input_str)
