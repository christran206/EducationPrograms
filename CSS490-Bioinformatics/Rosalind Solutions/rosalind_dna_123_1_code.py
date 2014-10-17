import csv
import sys
print("Given a DNA string, will return four integer values in the order of A C G T")
textin = input("DNA String: ")
count = [0, 0, 0, 0]
for char in textin:
    if char == 'A':
        count[0] += 1
    if char == 'C':
        count[1] += 1
    if char == 'G':
        count[2] += 1
    if char == 'T':
        count[3] += 1
print(' '.join(map(str,count)))