__author__ = 'Christopher'

infile = open(raw_input("Name of text file: "), 'r')

dna = infile.readline().strip()
motif = infile.readline().strip()
locations = []

for i in range(len(dna)-len(motif)):
    if(dna[i:i+len(motif)] == motif):
        locations.append(i+1)

print(' '.join(map(str,locations)))