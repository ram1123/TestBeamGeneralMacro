import os
import subprocess

#pathOfInputFile="/home/ramkrishna/TEMP/LogFiles_TB/LogFiles306To407"    # Modified by user
#pathOfInputFile="/home/ramkrishna/TEMP/LogFiles_TB/2014H2C_LogFiles_1257To1312_1398To1426"
#pathOfInputFile="/home/ramkrishna/TEMP/LogFiles_TB/2014H4C_LogFiles_2064To2123"
#pathOfInputFile="/home/ramkrishna/TEMP/LogFiles_TB/2014H2C_LogFiles_1313To1397"
#pathOfInputFile="/home/ramkrishna/TEMP/LogFiles_TB/2014H4A_LogFiles_1592To1646"
pathOfInputFile="/home/ramkrishna/TEMP/LogFiles_TB/2014H4C_LogFiles_1868To1906"

#for n in range(306,307):                                                # Modified by user
for n in range(1048):                                                # Modified by user
    #os.system('grep Run0306 RunList.dat')
    #output = subprocess.check_output("grep Run0306 RunList.dat", shell=True)
    #print "Output = ",n
    #output = output.replace(" ", "")
    #with open("H4RunList.dat") as openfile:                               # This input file list is for H2 only
    with open("RunList.dat") as openfile:                               # This input file list is for H2 only
        for line in openfile:
            for part in line.split():
                if "Run"+str(n) in part:                               # Modified by user "Run0" should be replaced accordingly
                    output=part
                    print "RunName : ",output
    print('root -l -b -q GE11sEfficiencyScan.C\('+str(n)+',\\"'+output+'\\",\\"'+pathOfInputFile+'\\"\)')
    os.system('root -l -b -q GE11sEfficiencyScan.C\('+str(n)+',\\"'+output+'\\",\\"'+pathOfInputFile+'\\"\)')
