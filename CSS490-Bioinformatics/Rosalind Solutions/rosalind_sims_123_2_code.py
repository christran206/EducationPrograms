__author__ = 'Christopher'
import urllib
import contextlib

infile = open(raw_input("Name of text file: "), 'r')
lines = (line.rstrip('\n') for line in infile)

string = []
#get fasta information into list
count = -1
for line in lines:
    if line[0] == '>':
        count += 1
        string.append("")
    else:
        string[count] += line

#duplicate string for comparisons
v,w = string

# Initialize the matrices.
S = [[0 for j in xrange(len(w)+1)] for i in xrange(len(v)+1)]
backtrack = [[0 for j in xrange(len(w)+1)] for i in xrange(len(v)+1)]

# Fill in the Score and Backtrack matrices.
for i in xrange(1, len(v)+1):
    for j in xrange(1, len(w)+1):
        scores = [S[i-1][j] - 1, S[i][j-1] - 1, S[i-1][j-1] + [-1, 1][v[i-1] == w[j-1]]]
        S[i][j] = max(scores)
        backtrack[i][j] = scores.index(S[i][j])

# Get the position of the highest scoring cell corresponding to the end of the shorter word w.
j = len(w)
i = max(enumerate([S[row][j] for row in xrange(len(w), len(v))]),key=lambda x: x[1])[0] + len(w)
max_score = S[i][j]

# Initialize the aligned strings as the input strings up to the position of the high score.
v_aligned, w_aligned = v[:i], w[:j]

# Quick lambda function to insert indels.
insert_indel = lambda word, i: word[:i] + '-' + word[i:]

# Backtrack to start of the fitting alignment.
while i*j != 0:
    if backtrack[i][j] == 0:
        i -= 1
        w_aligned = insert_indel(w_aligned, j)
    elif backtrack[i][j] == 1:
        j -= 1
        v_aligned = insert_indel(v_aligned, i)
    elif backtrack[i][j] == 2:
        i -= 1
        j -= 1

# Cut off v at the ending point of the backtrack.
v_aligned = v_aligned[i:]

print(str(max_score))
print(v_aligned)
print(w_aligned)