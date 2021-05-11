#include "py_lib.h"
#include "caffe_dnn.h"
#include "tf_dnn.h"
#include "fpga_api.h"
#include <string>
#include <stdio.h>
#include <iostream>

void *getCaffeNet(void *network, int m_size, int v_size)
{
  char *net_char = static_cast<char *>(network);
  FPGA *dev = new FPGA(0x40000000, 0x43c00000, m_size, v_size);
  return new CaffeDNN(std::string(net_char), dev);
}

void delCaffeNet(void *net_ptr)
{
  CaffeDNN *net = static_cast<CaffeDNN *>(net_ptr);
  FPGA *dev = net->getDev();

  delete net;
  delete dev;
}

void inferenceCaffe(void *net_ptr, const void *in, void *out, int *num_call)
{
  CaffeDNN *net = static_cast<CaffeDNN *>(net_ptr);
  const float *ret = net->run(static_cast<const float *>(in));

  float *output = static_cast<float *>(out);
  for (int i = 0; i < 10; ++i)
  {
    output[i] = ret[i];
  }
  *num_call = net->total_block_call();
}

void *getTFNet(void *network, int m_size, int v_size)
{
  char *net_char = static_cast<char *>(network);
  FPGA *dev = new FPGA(0x40000000, 0x43c00000, m_size, v_size);
  return new TFDNN(std::string(net_char), dev);
}

void delTFNet(void *net_ptr)
{
  TFDNN *net = static_cast<TFDNN *>(net_ptr);
  FPGA *dev = net->getDev();

  delete net;
  delete dev;
}

void inferenceTF(void *net_ptr, const void *in, void *out, int *num_call)
{
  TFDNN *net = static_cast<TFDNN *>(net_ptr);
  const float *ret = net->run(static_cast<const float *>(in));

  float *output = static_cast<float *>(out);
  for (int i = 0; i < 10; ++i)
  {
    output[i] = ret[i];
  }
  *num_call = net->total_block_call();
}
