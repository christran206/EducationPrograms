__author__ = 'Christopher'
import math
from itertools import product


infile = open(raw_input("Name of text file: "), 'r')

lexicons = infile.readline()
lexicons = lexicons.strip().split(" ")
length = int(infile.readline())

print(lexicons)
print(length)


lexList = product(lexicons,repeat=length)

for lex in lexList:
    print(''.join(lex))