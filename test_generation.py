#
#
#	Code to generate random testcases for CP
#	To generate the testcases, run this file
#	with a random number as an argument. Note that 
#	the same random number will always give the same 
#	input case.
#
#
import sys
import random

#initialising random using the command line seed
mseed = int(sys.argv[1])
random.seed(mseed)

input_file = open('input.txt' , 'w')

#use random.randint(p , q) to get a random integer in the range [p , q].
#use the following code to write n space separated integers followed by a newline'
#character
"""
	suppose the numbers are c1,c2,...,cn
	for i in range (1 , n + 1):
		if (i == 1):
			print(str(c1))
		else 
			print(" " + str(ci))

"""


#only make changes below this code
t = random.randint(1 , 3)
input_file.write(str(t) + "\n")

while (t > 0):
	x = random.randint(1 , 10)
	n = 2 * x

	l = random.randint(0 , n)
	r = n - l

	input_file.write(str(n) + " " + str(l) + " " + str(r) + "\n")

	for i in range (1 , n + 1):
		ci = random.randint(1 , n)
		if (i == 1):
			input_file.write(str(ci))
		else:
			input_file.write(" " + str(ci))
	input_file.write("\n")
	t = t - 1

