#!/usr/bin/python3

# run the following script to get the test.dat a binary database file with random records
# > for big and < for little endian byte order in struct.pack
import string
import random
import struct
  
# initializing size of string 
N = 32
fh=open("test.dat", "wb")
stream=["COMP", "ELEC", "ENTC", "CIVIL", "MECH", "INSTRU", "PROD", "META"]
# using random.choices()
# generating random strings 
for i in range(1024):
    mis=i+1
    tempstream=stream[random.randint(0,7)]
    res = ''.join(random.choices(string.ascii_uppercase , k = N))
    cgpa=round(random.uniform(0.00, 10.00), 2)
    studRec=struct.pack('<i128s128sf',mis,bytes(res,'utf-8'),bytes(tempstream,'utf-8'), cgpa)
    fh.write(studRec)
fh.close()
