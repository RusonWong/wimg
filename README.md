wimg
====

WIMG:Distributed Image Storage and Processing system


Learned a lot from zimg:https://github.com/buaazp/zimg

Dependency
------------
[libevent](https://github.com/libevent/libevent): Provides a sophisticated framework for buffered network IO.  
[memcached](https://github.com/memcached/memcached): A distributed memory object caching system.  
[protobuf](http://code.google.com/p/protobuf/): Google fast data Serialization protocol.    
[imagemagick](http://www.imagemagick.org/script/magick-wand.php): A software suite to create, edit, compose, or convert bitmap images.  

Build
------------
you should setup enviroment first.

### openssl
    wget http://www.openssl.org/source/openssl-1.0.1g.tar.gz 
    tar zxvf  openssl-1.0.1g.tar.gz 
    ./config shared --prefix=/usr/local --openssldir=/usr/ssl 
    make && make install 
    
### libevent
    wget http://cloud.github.com/downloads/libevent/libevent/libevent-2.0.21-stable.tar.gz 
    tar zxvf libevent-2.0.17-stable.tar.gz 
    ./configure --prefix=/usr/local 
    make && make install 
    
### imagemagick
    wget ftp://ftp.kddlabs.co.jp/graphics/ImageMagick/ImageMagick-6.8.9-8.tar.gz
    tar xzvf ImageMagick-6.8.9-8.tar.gz 
    cd ImageMagick-6.8.9-0 
    ./configure  --prefix=/usr/local 
    make && make install 
    
### libmemcached
    wget https://launchpad.net/libmemcached/1.0/1.0.18/+download/libmemcached-1.0.18.tar.gz
    tar zxvf libmemcached-1.0.18.tar.gz
    cd libmemcached-1.0.18
    ./configure -prefix=/usr/local --with-memcached 
    make &&　make install 

### memcached
    wget http://www.memcached.org/files/memcached-1.4.19.tar.gz
    tar zxvf memcached-1.4.19.tar.gz
    cd memcached-1.4.19
    ./configure --prefix=/usr/local
    make
    make install

### protocol buffer
    wget http://protobuf.googlecode.com/files/protobuf-2.5.0.tar.gz
    tar -zxvf protobuf-2.5.0.tar.gz
    ./configure
    make && make install
    ldconfig


### beansdb
    git clone https://github.com/douban/beansdb
    cd beansdb
    ./configure --prefix=/usr/local
    make
    [run aclocal if 'error: possibly undefined macro: AM_INIT_AUTOMAKE' occurs]

Build Wimg
==========
    sudo apt-get install openssl libevent-dev libmagickwand-dev libmemcached-dev
    cd [WIMG_ROOT]
    make

Three executable files will be created(wmaster/wmaster, wnode/wnode, wclient/wclient)

There are more to be done!
=============





