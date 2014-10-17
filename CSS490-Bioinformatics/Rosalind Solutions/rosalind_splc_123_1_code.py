__author__ = 'Christopher'
import Bio.Seq

infile = open(raw_input("Name of text file: "), 'r')

lines = (line.rstrip('\n') for line in infile)
hasInitial = False
newSection = False
for line in lines:
    if line[0] != '>':
        if not hasInitial:
            initialDNA = line
            print(initialDNA)
            hasInitial = True
        else :
            #print(line)
            initialDNA = initialDNA.replace(line, '')
print(initialDNA)
print(Bio.Seq.translate(initialDNA,stop_symbol=''))