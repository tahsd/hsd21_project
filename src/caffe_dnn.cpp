#include "caffe_dnn.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>

CaffeDNN::CaffeDNN(std::string model, FPGA *dev) : CommonDNN(dev)
{
  {
    std::fstream input(model.c_str(), std::ios::in | std::ios::binary);
    if (!net_.ParseFromIstream(&input))
    {
      assert(0 && "Failed to parse network.");
    }
  }

  // assumption 1: input data is provided by "data" blob and input size is 28 x 28
  // assumption 2: the first input blob of Softmaxloss layer is connected to final ouptut of network
  input_idx_ = regDataIdx("data", 28 * 28);

  for (int i = 0; i < net_.layer().size(); ++i)
  {
    if (std::string(net_.layer(i).type()).compare("InnerProduct") == 0)
    {
      const float *weight = net_.layer(i).blobs(0).data().data();
      const float *bias = nullptr;

      if (net_.layer(i).inner_product_param().bias_term())
        bias = net_.layer(i).blobs(1).data().data();

      std::string input = net_.layer(i).bottom(0);
      std::string output = net_.layer(i).top(0);

      int in_idx = getDataIdx(input);
      int input_size = data_[in_idx].size();

      int output_size = net_.layer(i).inner_product_param().num_output();
      int out_idx = regDataIdx(output, output_size);

      // append new op
      ops_.push_back(std::move(std::unique_ptr<Op>(new MatVecOp(dev_, weight, bias, input_size, output_size))));
      op_pair_.push_back({in_idx, out_idx});
    }
    else if (std::string(net_.layer(i).type()).compare("ReLU") == 0)
    {
      std::string input = net_.layer(i).bottom(0);
      std::string output = net_.layer(i).top(0);

      int in_idx = getDataIdx(input);
      int input_size = data_[in_idx].size();

      int output_size = input_size;
      int out_idx = regDataIdx(output, output_size);

      ops_.push_back(std::move(std::unique_ptr<Op>(new ReLUOp(input_size))));
      op_pair_.push_back({in_idx, out_idx});
    }
    else if (std::string(net_.layer(i).type()).compare("SoftmaxWithLoss") == 0)
    {
      std::string input = net_.layer(i).bottom(0);
      std::string output = "prob";

      int in_idx = getDataIdx(input);
      int input_size = data_[in_idx].size();

      int output_size = input_size;
      int out_idx = regDataIdx(output, output_size);

      ops_.push_back(std::move(std::unique_ptr<Op>(new SoftmaxOp(input_size))));
      op_pair_.push_back({in_idx, out_idx});

      output_idx_ = out_idx;
    }
  }
}
