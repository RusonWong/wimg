from django.shortcuts import render
from django.http import HttpResponse
from django.template import RequestContext, loader
import os,sys

from wimgsdk import wclient

def getLocalFile(fileName):
	path =  "./imgs/" + fileName
	f = open(path,"r")
	content = f.read()
	f.close()
	return content

def index(request):
	fileKey = request.GET.get("file")
	width = request.GET.get("w")
	height = request.GET.get("h")

	imgContent = wclient.getImage(fileKey,int(width),int(height))
	print "size is:", len(imgContent)
	response = HttpResponse(imgContent, content_type = 'image/jpeg')

	return response

def upload(request):
	file_obj = request.FILES.get('userfile', None)
	if not file_obj:
		return HttpResponse("no input file")

	imgContent = file_obj.read(file_obj.size)
	print "imgContent size sent:",len(imgContent)

	newname = wclient.uploadImage(file_obj.name, imgContent)

	imgHref = '/wimg/img?file='+newname+'&w=500&h=500'
	ret = '<html><a href="'+ imgHref +'" >' + newname + '</a>' +'</html>'
	return HttpResponse(ret)

def upload_page(request):
	template = loader.get_template('upload_page.html')
	context = RequestContext(request,{})
	return HttpResponse(template.render(context))

def img(request):
	fileKey = request.GET.get("file")
	width = request.GET.get("w")
	height = request.GET.get("h")

	imgContent = wclient.getImage(fileKey,int(width),int(height))
	response = HttpResponse(imgContent, content_type = 'image/jpeg')
	return response