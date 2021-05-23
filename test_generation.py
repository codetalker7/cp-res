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
#use input_file.write(string) to write something.
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
t = random.randint(1 , 1)
input_file.write(str(t) + "\n")

while (t > 0):
	#change code only here
	n = random.randint(1 , 10)
	m = 20
	input_file.write(str(n) + " " + str(m) + "\n")
    
	mlist = [0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0]
	for i in range (1 , n + 1):
		x = 1
		while (mlist[x] == 1):
			x = random.randint(1 , 19)
		mlist[x] = 1
		if (i == 1):
			input_file.write(str(x))
		else:
			input_file.write(" " + str(x))
	input_file.write("\n")

	m1list = ['L' , 'R']
	for i in range (1 , n + 1):
		y = random.randint(0 , 1)	
		c = m1list[y]
		if (i == 1):
			input_file.write(str(c))
		else:
			input_file.write(" " + str(c))
	input_file.write("\n")


    #do not change this
	t = t - 1


