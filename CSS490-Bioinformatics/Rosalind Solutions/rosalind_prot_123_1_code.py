import csv
import sys

print("Takes in a RNA sequence and outputs protein string")

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

infile = open(raw_input("Name of text file: "),'r')
rnaString = infile.readline()
codonSequence = []
if (len(rnaString) -1) % 3 == 0:
    index = 0
    while index < len(rnaString)-1:
        codon = rnaString[index: index+3]
        protein = CODON[codon]
        if protein == 'Z':
            break
        codonSequence.append(protein)
        index += 3

infile.close()
print(''.join(codonSequence))