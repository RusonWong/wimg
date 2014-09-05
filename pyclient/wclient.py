
import sys
import os
from socket import *
import WPB_pb2
import util
import hashlib

MASTER_ADDR = "127.0.0.1"
MASTER_PORT = 8888

def getLocalFile(fileName):
	path = "./files/" + fileName
	f = open(path,"r")
	content = f.read()
	f.close()
	return content

def writeLocalFile(fileName, content):
	path = "./files/" + fileName
	f = open(path, "w")
	f.write(content)
	f.close()


def do_connect(addr ,port):
	ADDR = (addr, port)
	client = socket(AF_INET, SOCK_STREAM)
	client.connect(ADDR)
	return client

def getNodeAddr(reqKey):
	client = do_connect(MASTER_ADDR, MASTER_PORT)
	#SEND METHOD
	util.w_send(client, "2")

	req = WPB_pb2.ReqSet() 
	req.md5 = reqKey

	reqBuff = req.SerializeToString()
	util.w_send(client, reqBuff)

	response = util.w_recv(client)

	nodeInfo = WPB_pb2.NodeInfo()
	nodeInfo.ParseFromString(response)
	#print "node info",nodeInfo.nodeAddr,nodeInfo.nodePort

	client.close()
	return nodeInfo.nodeAddr,nodeInfo.nodePort

def uploadImage(imgName, imgContent):
	#get file content
	content = imgContent

	reqKey = hashlib.md5(content).hexdigest()
	#print "content key is ",reqKey

	nodeAddr,nodePort = getNodeAddr(reqKey)

	nodeSocket = do_connect(nodeAddr, nodePort)
	#send method
	util.w_send(nodeSocket, "2")
	req = WPB_pb2.ReqSet()
	req.md5 = reqKey
	req.imageName = imgName

	util.w_send_pb(nodeSocket, req)
	#send file content
	util.w_send(nodeSocket, content)
	#get Response
	response = WPB_pb2.ReqResponse()
	respBuff = util.w_recv(nodeSocket)
	response.ParseFromString(respBuff)

	print "resp:new name is:", response.newname
	nodeSocket.close()
	return response.newname


def getImage(key, width, height):
	#get node
	nodeAddr,nodePort = getNodeAddr(key)
	nodeSocket = do_connect(nodeAddr, nodePort)
	#send method
	util.w_send(nodeSocket, "1")

	req = WPB_pb2.ReqGet()
	req.imageID = key
	req.width = width
	req.height = height
	req.keep_proportion = True

	util.w_send_pb(nodeSocket,req)

	response = WPB_pb2.ReqResponse()
	respBuff = util.w_recv(nodeSocket)
	
	response.ParseFromString(respBuff)
	if response.rspCode == WPB_pb2.REQ_FAILED:
		print "ERROR GET IMAGE"
		return
   	
   	#get content
   	imgContent = util.w_recv(nodeSocket)

   	
   	nodeSocket.close()
 	return imgContent

 	
while(True):
	cmd = raw_input("command:")
	if not cmd:
		break;

	cmd_items = cmd.split(" ")
	cmd_items = [item for item in cmd_items if item != ""]
	
	if cmd_items[0] == "upload" and len(cmd_items) == 2:
		fileName = cmd_items[1]	
		imgContent = getLocalFile(fileName)
		uploadImage(fileName, imgContent)
	elif cmd_items[0] == "get" and len(cmd_items) == 4:
		key = cmd_items[1]
		width = int(cmd_items[2])
		height = int(cmd_items[3])
		imgContent = getImage(key, width, height)
		writeLocalFile(key+".jpg", imgContent)



