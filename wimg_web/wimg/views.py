from django.shortcuts import render
from django.http import HttpResponse
from django.template import RequestContext, loader
import os,sys

from wimgsdk import wclient


def __render2Response(request, template_src, params = {}):
	template = loader.get_template(template_src)
	context = RequestContext(request,params)
	return HttpResponse(template.render(context))


def getLocalFile(fileName):
	path =  "./imgs/" + fileName
	f = open(path,"r")
	content = f.read()
	f.close()
	return content

def index(request):
	return __render2Response(request, 'welcome.html')

def upload(request):
	file_obj = request.FILES.get('userfile', None)
	if not file_obj:
		return HttpResponse("no input file")

	imgContent = file_obj.read(file_obj.size)
	print "imgContent size sent:",len(imgContent)
	newname = wclient.uploadImage(file_obj.name, imgContent)
	imgHref = '/wimg/img?k='+newname+'&w=500&h=500'
	ret = '<html><a href="'+ imgHref +'" >' + newname + '</a>' +'</html>'
	return HttpResponse(ret)

def upload_page(request):
	return __render2Response(request, 'upload_page.html')

def img(request):
	fileKey = request.GET.get("k")
	width = request.GET.get("w")
	height = request.GET.get("h")

	if not fileKey:
		return __render2Response(request, 'welcome.html')

	imgContent = wclient.getImage(fileKey,int(width),int(height))
	response = HttpResponse(imgContent, content_type = 'image/jpeg')
	return response

def test_local(request):
	content = getLocalFile("test.jpg");
	response = HttpResponse(content, content_type = 'image/jpeg')
	return response
