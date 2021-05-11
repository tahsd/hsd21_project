CPP = g++
CPPFLAGS = -std=c++11 -O3
PROTO = ./proto
SRC = ./src
BUILD = ./build
INCLUDE =  -I ./include -I$(PROTO)
DATA_DIR = ./data
MODEL_DIR = ./pretrained_weights

all: cpu fpga
cpu: $(BUILD)/libpylib_cpu.so
fpga: $(BUILD)/libpylib_fpga.so

clean:
	rm -f $(BUILD)/caffe_dnn.o
	rm -f $(BUILD)/fpga_api.o
	rm -f $(BUILD)/fpga_api_on_cpu.o
	rm -f $(BUILD)/libpylib_cpu.so
	rm -f $(BUILD)/libpylib_fpga.so
	rm -f $(BUILD)/py_lib.o
	rm -f $(BUILD)/tf_dnn.o

distclean:
	rm -f $(PROTO)/caffe.pb.* ./build/* 
	rm -f $(DATA_DIR)/*-ubyte
	rm -f $(MODEL_DIR)/*.caffemodel
	#rm -f $(MODEL_DIR)/*.txt

OBJECTS=$(BUILD)/py_lib.o $(BUILD)/caffe.pb.o $(BUILD)/caffe_dnn.o $(BUILD)/tf_dnn.o $(BUILD)/common_dnn.o

$(PROTO)/caffe.pb.h : $(PROTO)/caffe.pb.cc	

$(PROTO)/caffe.pb.cc : $(PROTO)/caffe.proto
	protoc -I=$(PROTO) --cpp_out=$(PROTO) $^

$(BUILD)/caffe.pb.o: $(PROTO)/caffe.pb.cc 
	$(CPP) -fPIC $(CPPFLAGS) -o $@ -c $^ 

$(BUILD)/common_dnn.o: $(SRC)/common_dnn.cpp $(PROTO)/caffe.pb.h ./include/ops.h
	$(CPP) -fPIC $(CPPFLAGS) $(INCLUDE) -o $@ -c $(SRC)/common_dnn.cpp 
	
$(BUILD)/caffe_dnn.o: $(SRC)/caffe_dnn.cpp $(PROTO)/caffe.pb.h ./include/ops.h
	$(CPP) -fPIC $(CPPFLAGS) $(INCLUDE) -o $@ -c $(SRC)/caffe_dnn.cpp 

$(BUILD)/tf_dnn.o: $(SRC)/tf_dnn.cpp ./include/ops.h
	$(CPP) -fPIC $(CPPFLAGS) $(INCLUDE) -o $@ -c $(SRC)/tf_dnn.cpp
	
$(BUILD)/py_lib.o: $(SRC)/py_lib.cpp $(BUILD)/caffe_dnn.o $(BUILD)/tf_dnn.o | $(PROTO)/caffe.pb.h
	$(CPP) -fPIC $(CPPFLAGS) $(INCLUDE) -o $@ -c $(SRC)/py_lib.cpp

$(BUILD)/libpylib_cpu.so: $(OBJECTS) $(BUILD)/fpga_api_on_cpu.o
	$(CPP) -shared -o $@  $^ -lprotobuf

$(BUILD)/libpylib_fpga.so: $(OBJECTS) $(BUILD)/fpga_api.o
	$(CPP) -shared -o $@  $^ -lprotobuf

$(BUILD)/fpga_api_on_cpu.o: $(SRC)/fpga_api_on_cpu.cpp
	$(CPP) -fPIC $(CPPFLAGS) $(INCLUDE) -o $@ -c $^ 

$(BUILD)/fpga_api.o: $(SRC)/fpga_api.cpp
	$(CPP) -fPIC $(CPPFLAGS) $(INCLUDE) -o $@ -c $^ 
	
