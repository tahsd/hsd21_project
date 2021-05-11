#ifndef _CAFFE_DNN_H_
#define _CAFFE_DNN_H_
#include "common_dnn.h"
#include "fpga_api.h"
#include "caffe.pb.h"

class CaffeDNN : public CommonDNN
{
private:
  caffe::NetParameter net_;
  caffe::NetParameter net_trained_;

public:
  CaffeDNN(std::string model, FPGA *dev);
};

#endif
