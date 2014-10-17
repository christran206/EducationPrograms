__author__ = 'Christopher'

infile = open(raw_input("Name of text file: "), 'r')

numbers = infile.readline()
numbers = numbers.split()
numbers = map(int,numbers)
numbers.sort()

original = list(numbers)
restrictionMap = {0}
startIndex = len(numbers) -1
index = len(numbers)-1

while len(numbers) > 0:
    newNumbers = list(numbers)

    y = newNumbers[index]
    #get all differences in restriction map
    differences = []
    for x in restrictionMap:
        differences.append(abs(y - x))
    #check if all differences exist in numbers
    skip = False
    for x in differences:
        if x in newNumbers:
            newNumbers.remove(x)
        else:
            index -= 1
            skip = True
            break
    #reset back to the original data if no indexes are found and then begin at one index lower
    if index < 0:
        numbers = list(original)
        restrictionMap = {0}
        startIndex -= 1
        index = startIndex
        continue
    if skip:
        continue
    else:
        numbers = list(newNumbers)
        restrictionMap.add(y)
        index = len(numbers)-1

sortedList = list(restrictionMap)
sortedList.sort()
print(' '.join(map(str,sortedList)))