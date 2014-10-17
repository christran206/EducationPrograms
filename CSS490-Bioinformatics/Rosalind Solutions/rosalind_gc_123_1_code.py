import csv
import sys

print("Takes in a Rosalind FASTA file and computes line with greatest GC-Content")

fasta = open(raw_input("Name of text file: "),'r')
maxGC = 0.0
global label

line = fasta.readline()
while line[0] != '>':
    line = fasta.readline()
    
while line:
    currentlabel = line
    line = fasta.readline()
    gcCount = 0.0
    length = 0
    while line and line[0] != '>':
        length += len(line)-1
        gcCount += line.count('G')
        gcCount += line.count('C')
        line = fasta.readline()
    gcContent = gcCount/length
    if(gcContent > maxGC):
        maxGC = gcContent
        label = currentlabel

fasta.close()
print(label[1:])
print("{:.6f}".format(maxGC*100))