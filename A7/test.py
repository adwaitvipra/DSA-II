
# Python3 code to demonstrate
# generating random strings 
# using random.choices()
import string
import random

  
# initializing size of string 
N = 63
dataset=[]
fh=open("newtest.txt", "w")
stream=["COMP", "ELEC", "ENTC", "CIVIL", "MECH", "INSTRU", "PROD", "META"]
# using random.choices()
# generating random strings 
for i in range(100000):
    mis=bin(random.randint(1, 100000))
    tempstream=stream[random.randint(0,7)]
    res = ''.join(random.choices(string.ascii_uppercase + string.ascii_lowercase, k = N))
    cgpa=bin(round(random.uniform(0.00, 10.00), 2))
    fh.write(mis)
    fh.write(tempstream)
    fh.write(res)
    fh.write(cgpa)
fh.close()