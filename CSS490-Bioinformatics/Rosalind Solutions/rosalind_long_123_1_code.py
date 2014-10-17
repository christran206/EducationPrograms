__author__ = 'Christopher'

infile = open(raw_input("Name of text file: "), 'r')
lines = (line.rstrip('\n') for line in infile)

string = []
count = -1
for line in lines:
    if line[0] == '>':
        count += 1
        string.append("")
    else:
        string[count] += line

while len(string) != 0:
    max_lengh = -1
    string1 = ""
    string2 = ""
    found = False

    #Check every string
    for prefix in xrange(len(string)):
        #against every other string
        for suffix in xrange(len(string)):
            #except itself
            if prefix != suffix:
                pfString = string[prefix]
                sfString = string[suffix]

                i = 0
                while pfString[i:] != sfString[0:len(pfString[i:])]:
                    i+=1

                if(len(pfString) - i > max_lengh):
                    found = True
                    max_lengh = len(pfString) - i
                    string1 = pfString
                    string2 = sfString
    if(found):
        string.remove(string1)
        string.remove(string2)
        newString = string1+string2[max_lengh:]
        string.append(newString)
    else:
        break

print(string)