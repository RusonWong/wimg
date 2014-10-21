#ifndef WCLIENT_H
#define WCLIENT_H

#include <iostream>
#include <string>
using namespace std;

int get_img(string md5, int width, int height, char* &content, size_t & content_len);
int upload_img(char* fileContent, size_t fileLen, string& ret_img_id);

#endif