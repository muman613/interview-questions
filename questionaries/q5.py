#!/usr/bin/python

"""
    Question #5 in Python, remove comments from 'json' string
"""


json = """
// this is a comment
{ // another comment
    "foo" : "True", // 3rd comment
    "url" : "http://www.google.com", // comment after URL
    "cred" : "Eat" // comment
}
"""


def remove_comments(line: str):
    """
    Implements a basic 'state-machine' which keeps track of whether the slashes occur in a 'literal' which is enclosed
    by quotation marks. If the slashes are inside a literal they are retained, otherwise the slashes are removed to the
    end of the line.

    :param line: Line to remove comments from.
    :return: Line with the comments removed.
    """
    in_literal, last_slash, lineout = False, False, ""

    for c in line:
        if in_literal:
            if c == '"':
                in_literal = False
            lineout += c
            continue
        if c == '"':
            in_literal = True
            last_slash = False
            lineout += c
            continue
        if c == "/":
            if last_slash is True:
                return lineout
            else:
                last_slash = True
        else:
            lineout += c

    if last_slash:
        lineout += "/"

    return lineout


def remove_comments_from_json(in_json: str):
    """
    Run through all the lines in the input text and assemble the lines with comments removed
    """
    out_json = []
    for line in in_json.split("\n"):
        out_json.append(remove_comments(line))

    return "\n".join(out_json)

print("Original JSON :")
print(json)

print("Stripped JSON :")
print(remove_comments_from_json(json))

