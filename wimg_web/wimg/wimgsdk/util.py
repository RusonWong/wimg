import sys
import os
from socket import *
import string

LEN_LEN = 10

def w_send(client, content):
	#get content len
	c_len = len(content)
	c_len_str = str(c_len)

	#construct len data
	c_len_len = len(c_len_str)
	len_temp = "\0" * (LEN_LEN - c_len_len)
	c_len_str = c_len_str + len_temp

	#send len
	client.send(c_len_str)
	#send content
	client.send(content)

def w_recv(client):
	#recv len
	c_len_str = client.recv(LEN_LEN)
	c_len_str = c_len_str.strip('\0')
	c_len = string.atoi(c_len_str)

	content = ""
	r_len = c_len

	while( r_len > 0):
		package = client.recv(c_len)
		content+=package
		r_len -= len(package)
	
	return content

def w_send_pb(client, pb):
	content = pb.SerializeToString()
	w_send(client, content)

