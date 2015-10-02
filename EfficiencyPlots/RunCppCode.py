import os
import subprocess
for n in range(306,408):
    #os.system('grep Run0306 RunList.dat')
    #output = subprocess.check_output("grep Run0306 RunList.dat", shell=True)
    #print "Output = ",output
    #output = output.replace(" ", "")
    with open("RunList.dat") as openfile:
        for line in openfile:
            for part in line.split():
                if "Run0"+str(n) in part:
                    output=part
    print('root -l -b -q GE11sEfficiencyScan.C\('+str(n)+',\\"'+output+'\\"\)')
    os.system('root -l -b -q GE11sEfficiencyScan.C\('+str(n)+',\\"'+output+'\\"\)')
