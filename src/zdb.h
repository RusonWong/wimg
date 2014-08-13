/*   
 *   zimg - high performance image storage and processing system.
 *       http://zimg.buaa.us 
 *   
 *   Copyright (c) 2013-2014, Peter Zhao <zp@buaa.us>.
 *   All rights reserved.
 *   
 *   Use and distribution licensed under the BSD license.
 *   See the LICENSE file for full text.
 * 
 */

/**
 * @file zdb.h
 * @brief Get and save image for ssdb/redis and beansdb/memcachedb backend functions' header.
 * @author 招牌疯子 zp@buaa.us
 * @version 2.0.0
 * @date 2014-04-16
 */


#ifndef ZDB_H
#define ZDB_H


#include "zcommon.h"

int get_img_mode_db(zimg_req_t *req, evhtp_request_t *request);

int get_img_db(thr_arg_t *thr_arg, const char *cache_key, char **buff, size_t *len);
int save_img_db(thr_arg_t *thr_arg, const char *cache_key, const char *buff, const size_t len);

int get_img_ssdb(redisContext* c, const char *cache_key, char **buff, size_t *len);
int save_img_ssdb(redisContext* c, const char *cache_key, const char *buff, const size_t len);
int get_img_beansdb(memcached_st *memc, const char *key, char **value_ptr, size_t *len);
int save_img_beansdb(memcached_st *memc, const char *key, const char *value, const size_t len);

int exist_beansdb(memcached_st *memc, const char *key);
int find_beansdb(memcached_st *memc, const char *key, char *value);
int set_beansdb(memcached_st *memc, const char *key, const char *value);
int del_beansdb(memcached_st *memc, const char *key);

#endif
