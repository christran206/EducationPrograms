import itertools
__author__ = 'Christopher'


infile = open(raw_input("Name of text file: "), 'r')
lines = (line.rstrip('\n') for line in infile)

string = []
count = -1
for line in lines:
    if line[0] == '>':
        count += 1
        string.append("")
    else:
        string[count] += line

#get all permutations from first string
sharedMotif = []
source = string.pop(0)

stringLength = len(string[0])
i = stringLength
while i > 1:
    for j in range(0,stringLength-i+1):
        if source[j:j+i] in string[0]:
            sharedMotif.append(source[j:j+i])
    i -= 1
string.pop(0)

#Check permutations against the remaining data and remove all non matching

for data in string:
    sharedMotif = [x for x in sharedMotif if x in data]


print(sharedMotif[0])
print(sharedMotif[1])
print(sharedMotif[2])
print(sharedMotif[3])
print(sharedMotif[4])