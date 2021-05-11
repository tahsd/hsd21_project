#include "common_dnn.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

CommonDNN::CommonDNN(FPGA *dev) : dev_(dev) {}

int CommonDNN::regDataIdx(string name, int size)
{
  int rtn = getDataIdx(name);
  if (rtn != -1)
  {
    return rtn;
  }
  else
  {
    data_.resize(data_.size() + 1);

    int idx = data_.size() - 1;
    data_[idx].resize(size);
    data_name2idx_[name] = idx;

    return idx;
  }
}

int CommonDNN::getDataIdx(string name)
{
  if (data_name2idx_.find(name) != data_name2idx_.end())
  {
    return data_name2idx_[name];
  }
  else
  {
    return -1;
  }
}

const float *CommonDNN::run(const float *input)
{
  memcpy(data_[input_idx_].data(), input, sizeof(float) * data_[input_idx_].size());

  for (int i = 0; i < ops_.size(); ++i)
  {
    auto &pair = op_pair_[i];
    ops_[i]->run(data_[pair.first].data(), data_[pair.second].data());
  }

  return data_[output_idx_].data();
}

int CommonDNN::total_block_call()
{
  return dev_->num_block_call();
}

FPGA *CommonDNN::getDev() { return dev_; }
