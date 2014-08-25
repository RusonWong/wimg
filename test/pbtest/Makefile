all: writer reader

writer: writer.cpp GetReq.pb.cc 
	g++ writer.cpp GetReq.pb.cc -o writer `pkg-config --cflags --libs protobuf`

reader: reader.cpp GetReq.pb.cc 
	g++ reader.cpp GetReq.pb.cc -o reader `pkg-config --cflags --libs protobuf`

clean:
	rm writer reader