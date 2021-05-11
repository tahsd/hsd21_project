#ifndef _TF_DNN_H_
#define _TF_DNN_H_
#include "common_dnn.h"
#include "fpga_api.h"

class TFDNN : public CommonDNN
{
public:
  TFDNN(std::string model, FPGA *dev);
};
#endif
