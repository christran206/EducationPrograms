import sys
import math

print("Takles two integers (a and b) and returns how many substrings of length b in length a")

integerInput = raw_input("Input two integers separated with a space: ")
ints = integerInput.split(" ")
ints = map(int, ints)
combinations = 0
for i in range(ints[1],ints[0]+1):
    combinations += math.factorial(ints[0])//(math.factorial(i)*math.factorial(ints[0]-i))
print(combinations)
print(combinations%1000000)