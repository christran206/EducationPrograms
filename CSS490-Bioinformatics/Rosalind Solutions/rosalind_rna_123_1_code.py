import csv
import sys

print("This application takes a DNA sequence and changes it to an RNA sequence")
print("Instances of T are replaced with U")
dna = raw_input("type in the DNA sequence: ")
dna = dna.replace('T','U')
print(dna)