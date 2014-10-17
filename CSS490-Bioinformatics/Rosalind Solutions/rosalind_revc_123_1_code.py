import csv
import sys

def complement(s):
    basecomplement = {'A': 'T', 'C': 'G', 'G': 'C', 'T': 'A'}
    letters = list(s)
    letters = [basecomplement[base] for base in letters]
    return ''.join(letters)
def revcom(s):
    return complement(s[::-1])

print("Takes a DNA string and returns reverse compliment")

dna = raw_input("DNA String: ")

print(revcom(dna))