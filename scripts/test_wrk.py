import os
import sys

url = "http://202.120.40.189:8081/test"
concurrent_levels = [10,20,30,40,50,100,200,300,400,500,1000]


for clevel in concurrent_levels:

	pcmd = "echo ...................concurrent_level: " + str(clevel) + "....................."
	os.system(pcmd)

	cmd = './wrk ' + ' -t' + str(10) + ' -c' + str(clevel) +' -d30s' + ' "' + url +'"'
	#print cmd
	for test_num in range(1,12):
		pcmd = "echo test#: " + str(test_num);
		os.system(pcmd)
		
		pcmd = "echo concurrent_level:" + str(clevel) + " test#:" + str(test_num) + ">proccess.txt"
		os.system(pcmd)
		
		os.system(cmd)
		os.system("echo ")
