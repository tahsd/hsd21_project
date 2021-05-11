#ifndef _PY_LIB_H_
#define _PY_LIB_H_

extern "C"
{
  void *getCaffeNet(void *network, int m_size, int v_size);
  void delCaffeNet(void *net_ptr);
  void inferenceCaffe(void *net_ptr, const void *in, void *out, int *num_call);
  void *getTFNet(void *network, int m_size, int v_size);
  void delTFNet(void *net_ptr);
  void inferenceTF(void *net_ptr, const void *in, void *out, int *num_call);
}

#endif
