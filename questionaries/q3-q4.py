#!/usr/bin/python

"""
    Question #3 & 4 in Python, determine if a string has balanced brackets.

    Michael Uman 12/04/2018

    OUTPUT:

    Sequence = ([{()}]())
    The sequence is balanced
    Sequence = ([{(])}]())
    The sequence is unbalanced
    Sequence = (())
    The sequence is balanced
    Sequence = (()(
    The sequence is unbalanced

"""

def balanced_brackets(in_str):
    stack = [] # The stack is used to determine if the brackets are closed in the correct order

    open_brackets = [ '(', '[', '{' ]

    for char in in_str:
        if char in open_brackets:
            stack.append(char)
        else:
            # Sequence MUST start with an open bracket
            if not stack:
                return False
            else:
                last = stack[-1] # Get the top of the stack
                if char is ")" and last is "(":
                    stack.pop()
                elif char is "]" and last is "[":
                    stack.pop()
                elif char is "}" and last is "{":
                    stack.pop()
                else:
                    stack.append(char)
    # The stack should be empty if the expression is balanced
    return stack == []


def test_sequence(seq):
    print("Sequence = {}".format(seq))
    if balanced_brackets(seq):
        print("The sequence is balanced")
    else:
        print("The sequence is unbalanced")
        

seq = "([{()}]())"
test_sequence(seq)
seq = "([{(])}]())"
test_sequence(seq)

# Sequences from Question 4

seq = "(())"
test_sequence(seq)
seq = "(()("
test_sequence(seq)

