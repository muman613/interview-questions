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
    """
    Determine if the input string contains a balanced order of brackets, meaning that each open bracket can contain other
    brackets but must be closed in the correct order.

    "(())" is balanced
    "())" is unbalanced
    :param in_str:
    :return:
    """
    stack = [] # The stack is used to determine if the brackets are closed in the correct order

    bracket_pairs = [
        ('(', ')'),     # Parenthesis
        ('[', ']'),     # Square Brackets
        ('{', '}')      # Curly Brackets
    ]

    def is_open_bracket(c):
        for bp in bracket_pairs:
            if bp[0] == c:
                return True
        return False

    def is_close_bracket(c, o):
        for bp in bracket_pairs:
            if (bp[1] == c) and (bp[0] == o):
                return True
        return False

    for char in in_str:
        if is_open_bracket(char):
            stack.append(char)
        else:
            # Sequence MUST start with an open bracket
            if not stack:
                return False
            else:
                last = stack[-1] # Get the top of the stack
                if is_close_bracket(char, last):
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
seq = "([])"
test_sequence(seq)
