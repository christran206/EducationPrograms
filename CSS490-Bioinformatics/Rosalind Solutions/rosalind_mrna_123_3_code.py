__author__ = 'Christopher'

FREQUENCY = {}
FREQUENCY["A"] = 4
FREQUENCY["C"] = 2
FREQUENCY["D"] = 2
FREQUENCY["E"] = 2
FREQUENCY["F"] = 2
FREQUENCY["G"] = 4
FREQUENCY["H"] = 2
FREQUENCY["I"] = 3
FREQUENCY["K"] = 2
FREQUENCY["L"] = 6
FREQUENCY["M"] = 1
FREQUENCY["N"] = 2
FREQUENCY["P"] = 4
FREQUENCY["Q"] = 2
FREQUENCY["R"] = 6
FREQUENCY["S"] = 6
FREQUENCY["T"] = 4
FREQUENCY["V"] = 4
FREQUENCY["W"] = 1
FREQUENCY["Y"] = 2
FREQUENCY["Z"] = 3

print("takes a protein string and returns possible combinations")

dna = raw_input("Protein String: ")

totalPossible = FREQUENCY["Z"]

if len(dna) > 0 :
    for i in range(1,len(dna)):
        #print(totalPossible)
        totalPossible *= FREQUENCY[dna[i]]

print(totalPossible)
print((totalPossible%1000000))