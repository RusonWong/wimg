import time
import threading


def getLocalFile(fileName):
	path = fileName
	f = open(path,"r")
	content = f.read()
	f.close()
	return content

last_proccess = ""
while True:
	new_proccess = getLocalFile("proccess.txt")
	if new_proccess != last_proccess:
		print new_proccess
		last_proccess = new_proccess
	time.sleep(1)


