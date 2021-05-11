import ctypes
import numpy as np


class Network(object):
  def __init__(self, args):
    self.m_size = args.m_size
    self.v_size = args.v_size
    self.run_type = args.run_type

    self.lib = ctypes.cdll.LoadLibrary("./build/libpylib_%s.so" % self.run_type)
    self.net = None

    self.total_num_call = np.zeros(1, dtype=np.int)
    self.output = np.zeros(10, dtype=np.float32)


class MLP(Network):
  def __init__(self, net_path, args):
    super(MLP, self).__init__(args)

    self.net = self.lib.getCaffeNet(ctypes.c_char_p(net_path.encode("utf-8")), self.m_size, self.v_size)

  def __del__(self):
    self.lib.delCaffeNet(self.net)

  def inference(self, input):
    self.lib.inferenceCaffe(self.net, input.ctypes.data, self.output.ctypes.data, self.total_num_call.ctypes.data)
    return self.output


class CNN(Network):
  def __init__(self, net_path, args):
    super(CNN, self).__init__(args)

    self.net = self.lib.getTFNet(ctypes.c_char_p(net_path.encode("utf-8")), self.m_size, self.v_size)

  def __del__(self):
    self.lib.delTFNet(self.net)

  def inference(self, input):
    self.lib.inferenceTF(self.net, input.ctypes.data, self.output.ctypes.data, self.total_num_call.ctypes.data)
    return self.output
