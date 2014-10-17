__author__ = 'Christopher'

inp = raw_input("String Input: ")

print(len(inp))
stringArray = {}

for i in range(0,len(inp)):
    stringArray[i] = inp[i:len(inp)]

#print(stringArray)

print(sorted(stringArray,key=stringArray.__getitem__))