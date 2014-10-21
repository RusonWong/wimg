#include <iostream>
#include <string>
#include <errno.h>
#include <evhtp.h>
#include "util.h"

#include "wclient.h"

using namespace std;


char* welcome_html;

void init()
{
    //init welcome_html
    char* welcome_html_content;
    size_t len;
    int r = get_local_file("static/welcome.html", welcome_html_content, len);

    welcome_html = welcome_html_content;
}


void 
reply_error(evhtp_request_t* req, char* msg)
{
    evhtp_headers_add_header(req->headers_out, evhtp_header_new("Content-Type", "text/html", 0, 0));
    evbuffer_add_printf(req->buffer_out,"%s", msg);
    evhtp_send_reply(req, EVHTP_RES_OK);
}


void 
welcome_cb(evhtp_request_t* req, void * a)
{
    cout<<"welcome called\n";
    const char* wpage = welcome_html;

    evhtp_headers_add_header(req->headers_out, evhtp_header_new("Content-Type", "text/html", 0, 0));
    evbuffer_add_printf(req->buffer_out,"%s", wpage);
    evhtp_send_reply(req, EVHTP_RES_OK);
}


int multipart_parse(evhtp_request_t* req, char* buff, size_t buff_len, char* content_type, string& img_id)
{
    char* boundary = NULL;
    char* boundary_end = NULL;

    int boundary_len = 0;
    char* boundaryPattern = NULL;

    cout<<"content type is:"<<content_type<<endl;
    if(strstr(content_type, "boundary") == NULL)
    {
        cout<<"boundary is not found in content type"<<endl;
        return -1;
    }

    boundary = strchr(content_type, '=');
    boundary++;
    boundary_len = strlen(boundary);

    if(boundary[0] == '"') 
    {
        boundary++;
        boundary_end = strchr(boundary, '"');
        if (!boundary_end) 
        {
            cout<<"Invalid boundary in multipart/form-data POST data"<<endl;
            return -1;
        }
    } 
    else 
    {
        /* search for the end of the boundary */
        boundary_end = strpbrk(boundary, ",;");
    }

    if (boundary_end) 
    {
        boundary_end[0] = '\0';
        boundary_len = boundary_end-boundary;
    }

    cout<<"boundary is "<<boundary<<endl;

    boundaryPattern = (char *)malloc(boundary_len + 3);
    snprintf(boundaryPattern, boundary_len + 3, "--%s", boundary);
    cout<<"boundary pattern is:"<<boundaryPattern<<endl;


    int start = -1, end = -1;
    const char *fileNamePattern = "filename=";
    const char *typePattern = "Content-Type";
    const char *quotePattern = "\"";
    const char *blankPattern = "\r\n";


    char* content_start = strstr(buff, boundaryPattern);
    //get file type

    //get file name
    char* fn_begin = strstr(buff, fileNamePattern);

    fn_begin = strchr(fn_begin, '\"');

    fn_begin += 1;

    char* fn_end = strstr(fn_begin, quotePattern);

    if(fn_begin == NULL || fn_end == NULL)
    {
        cout<<"failed to parse"<<endl;
        return -1;
    }
    int len = fn_end - fn_begin;

    char* name_buff = (char*)malloc(len + 1);
    snprintf(name_buff, len + 1, "%s", fn_begin);
    name_buff[len + 1] = '\0';
    cout<<"fileName is:"<<name_buff<<endl;

    ////////////////get content type begein////////////////
    char* ct_begin = strstr(buff, typePattern);
    ct_begin += strlen(typePattern);
    
    while(ct_begin[0] == ' ' || ct_begin[0] == ':')
    {
        ct_begin ++;
    }

    char* ct_end = strstr(ct_begin, blankPattern);

    int type_len = ct_end - ct_begin;
    //cout<<"type len is:"<<type_len<<endl;
    printStr(ct_begin,0,type_len);
    ////////////////get content type end////////////////

    //////////////////////get img content start///////////////
    char* content_begin = ct_end + 4;
    //printStr(content_begin,0,10);
    //cout<<content_begin<<endl;
    //find the next bounadary
    /*
    char* content_end = strstr(content_begin, boundaryPattern);
    if (content_end == NULL)
    {
        cout<<"cannot find boundary_end\n";
        return;
    }
    content_end -= 2;

    int img_len = content_end - content_begin;
    cout<<img_len<<endl;
    cout<<content_begin<<endl;
    */
    char* content_end = buff + buff_len - strlen(boundaryPattern) - 6;
    printStr(content_end,0,5);

    int content_len = content_end - content_begin;
    cout<<"content len is:"<<content_len<<endl;

    string img_key;
    int ret = upload_img(content_begin,content_len, img_key);

    if(ret == 1)
    {
        cout<<"new img key is:"<<img_key<<endl;
        img_id = img_key;
    }

    return 1;
    //printStr(content_begin,0 , img_len);
    //write_local_file("img.jpg",content_begin, content_len);
}

void 
upload_cb(evhtp_request_t* req, void* a)
{
    cout<<"upload called\n";
    const char* wpage = "upload page";

    int req_method = evhtp_request_get_method(req);
    if(req_method >= 16)
        req_method = 16;


    const char *content_len = evhtp_header_find(req->headers_in, "Content-Length");

    int post_size = atoi(content_len);
    cout<<"content len is:"<<post_size<<endl;

    evbuf_t *buf;
    buf = req->buffer_in;
    char* buff = (char *)malloc(post_size);
 
    int rmblen, evblen;

    while((evblen = evbuffer_get_length(buf)) > 0)
    {
        cout<<"evblen:"<< evblen <<endl;
        rmblen = evbuffer_remove(buf, buff, evblen);
        cout<<"rmblen:"<<rmblen<<endl;
        if(rmblen < 0)
        {
            cout<<"evbuffer_remove failed!"<<endl;
        }
    }
//  write_local_file("temp.jpg",buff,post_size);

    const char *content_type = evhtp_header_find(req->headers_in, "Content-Type");

    string img_id;
    int ret = multipart_parse(req, buff, post_size, (char*)content_type, img_id);
    cout<< ret<<endl;
    if(ret == 1)
    {
        string img_href = "img?k=" + img_id + "&" + "w=300&h=300";
        cout<<img_href<<endl;

        string html_content = "<html><head><title>wimg</title></head><body><a href=\"" + img_href +"\">" + img_id + "</a></body></html>";
        cout<<html_content<<endl;
        evhtp_headers_add_header(req->headers_out, evhtp_header_new("Content-Type", "text/html", 0, 0));
        evbuffer_add_printf(req->buffer_out,"%s", html_content.c_str());
        evhtp_send_reply(req, EVHTP_RES_OK);
    }
    else
    {
        evhtp_headers_add_header(req->headers_out, evhtp_header_new("Content-Type", "text/html", 0, 0));
        evbuffer_add_printf(req->buffer_out,"%s", "upload failed!");
        evhtp_send_reply(req, EVHTP_RES_OK);
    }
}



void 
get_img_cb(evhtp_request_t* req, void* a)
{

    const char *uri;
    uri = req->uri->path->full;
    const char *rfull = req->uri->path->full;
    const char *rpath = req->uri->path->path;
    const char *rfile= req->uri->path->file;

    cout<<"full:"<<rfull<<endl;
    cout<<"rpath:"<<rpath<<endl;
    cout<<"rfile:"<<rfile<<endl;

    evhtp_kvs_t *params;
    params = req->uri->query;

    const char* str_k = evhtp_kv_find(params, "k");
    const char* str_w = evhtp_kv_find(params, "w");
    const char* str_h = evhtp_kv_find(params, "h");

    cout<<"k:"<<str_k<<endl;
    cout<<"w:"<<str_w<<endl;
    cout<<"h:"<<str_h<<endl;

    int w = atoi(str_w);
    int h = atoi(str_h);

    string md5(str_k);
    char* content;
    size_t content_len;

    int ret = get_img(md5, w, h, content, content_len);

    if(ret == 1)
    {
        evhtp_headers_add_header(req->headers_out, evhtp_header_new("Content-Type", "image/jpeg", 0, 0));
        evbuffer_add(req->buffer_out,content, content_len);
        evhtp_send_reply(req, EVHTP_RES_OK);

        delete content;
    }
    else
    {
        evhtp_headers_add_header(req->headers_out, evhtp_header_new("Content-Type", "text/html", 0, 0));
        evbuffer_add_printf(req->buffer_out,"%s", "error get img");
        evhtp_send_reply(req, EVHTP_RES_OK);
    }

}


void gen_cb(evhtp_request_t* req, void* a)
{
    cout<<"not configured\n";
    evbuffer_add_printf(req->buffer_out,"%s", "404 not found, or not configured");
    evhtp_send_reply(req, EVHTP_RES_OK);
}

int
main(int argc, char ** argv) {

    init();

    evbase_t * evbase = event_base_new();
    evhtp_t  * htp    = evhtp_new(evbase, NULL);

    evhtp_set_cb(htp, "/welcome", welcome_cb, (void*)"simple");
    evhtp_set_cb(htp, "/img", get_img_cb, (void*)"simple");
    evhtp_set_cb(htp, "/upload", upload_cb, NULL);


    evhtp_set_gencb(htp, gen_cb, NULL);


#ifndef EVHTP_DISABLE_EVTHR
    evhtp_use_threads(htp, NULL, 4, NULL);
#endif
    evhtp_bind_socket(htp, "0.0.0.0", 8081, 1024);

    event_base_loop(evbase, 0);

    evhtp_unbind_socket(htp);
    evhtp_free(htp);
    event_base_free(evbase);

    return 0;
}

