__author__ = 'Christopher'
import Bio.Seq
import sys

infile = open(raw_input("Name of text file: "), 'r')

coding_dna = infile.readline()
print(coding_dna)
print(len(coding_dna))
protein_string = infile.readline()
protein_result = Bio.Seq.translate(coding_dna,stop_symbol="", to_stop=False)
print(protein_result)