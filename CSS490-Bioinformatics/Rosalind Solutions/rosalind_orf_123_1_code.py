import csv
import sys
import sets

CODON = {}
CODON["AAA"] = 'K'
CODON["AAC"] = 'N'
CODON["AAG"] = 'K'
CODON["AAU"] = 'N'
CODON["ACA"] = 'T'
CODON["ACC"] = 'T'
CODON["ACG"] = 'T'
CODON["ACU"] = 'T'
CODON["AGA"] = 'R'
CODON["AGC"] = 'S'
CODON["AGG"] = 'R'
CODON["AGU"] = 'S'
CODON["AUA"] = 'I'
CODON["AUC"] = 'I'
CODON["AUG"] = 'M'
CODON["AUU"] = 'I'
CODON["CAA"] = 'Q'
CODON["CAC"] = 'H'
CODON["CAG"] = 'Q'
CODON["CAU"] = 'H'
CODON["CCA"] = 'P'
CODON["CCC"] = 'P'
CODON["CCG"] = 'P'
CODON["CCU"] = 'P'
CODON["CGA"] = 'R'
CODON["CGC"] = 'R'
CODON["CGG"] = 'R'
CODON["CGU"] = 'R'
CODON["CUA"] = 'L'
CODON["CUC"] = 'L'
CODON["CUG"] = 'L'
CODON["CUU"] = 'L'
CODON["GAA"] = 'E'
CODON["GAC"] = 'D'
CODON["GAG"] = 'E'
CODON["GAU"] = 'D'
CODON["GCA"] = 'A'
CODON["GCC"] = 'A'
CODON["GCG"] = 'A'
CODON["GCU"] = 'A'
CODON["GGA"] = 'G'
CODON["GGC"] = 'G'
CODON["GGG"] = 'G'
CODON["GGU"] = 'G'
CODON["GUA"] = 'V'
CODON["GUC"] = 'V'
CODON["GUG"] = 'V'
CODON["GUU"] = 'V'
CODON["UAA"] = 'Z'
CODON["UAC"] = 'Y'
CODON["UAG"] = 'Z'
CODON["UAU"] = 'Y'
CODON["UCA"] = 'S'
CODON["UCC"] = 'S'
CODON["UCG"] = 'S'
CODON["UCU"] = 'S'
CODON["UGA"] = 'Z'
CODON["UGC"] = 'C'
CODON["UGG"] = 'W'
CODON["UGU"] = 'C'
CODON["UUA"] = 'L'
CODON["UUC"] = 'F'
CODON["UUG"] = 'L'
CODON["UUU"] = 'F'

def complement(s):
    basecomplement = {'A': 'U', 'C': 'G', 'G': 'C', 'U': 'A'}
    letters = list(s)
    letters = [basecomplement[base] for base in letters]
    return ''.join(letters)
def revcom(s):
    return complement(s[::-1])

print("Takes in a Rosalind FASTA file and computes Protein Strings with Open Reading Frames")

fasta = open(raw_input("Name of text file: "),'r')
totalSequences = []
line = fasta.readline()

while line[0] != '>':
    line = fasta.readline()

while line:
    #print("processing fasta line: " + line)
    label = line
    line = fasta.readline()
    line = line.replace('T','U')
    lines = [line, revcom(line)]

    for dna in lines:
        #print("processing line: " + dna)
        sIndex = 0
        while(sIndex+3 < len(dna)):
            currentProtein = dna[sIndex:sIndex+3]
            if(currentProtein == "AUG"):
                #print("Start found at index: "+str(sIndex))
                proteinSequence = ["M"]
                s2Index = sIndex+3
                while(s2Index+3 <= len(dna)):
                    protein = CODON[dna[s2Index:s2Index+3]]
                    if(protein == 'Z'):
                        totalSequences.append(''.join(proteinSequence))
                        break
                    proteinSequence.append(protein)
                    s2Index += 3
            sIndex += 1
    line = fasta.readline()

print('\n'.join(set(totalSequences)))
fasta.close()