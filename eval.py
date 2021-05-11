#-*- coding: utf-8 -*-

import numpy as np
import pprint as pp
import os
import time
import argparse

from models import MLP, CNN
from data.load_mnist import load_mnist


parser = argparse.ArgumentParser(description='Neural Network Accleration on FPGA')
parser.add_argument('--num_test_images', type=int, default=100, help='The number of test images (range: 1~10000)')
parser.add_argument('--m_size', type=int, default=16, help='The number of row in the block operation')
parser.add_argument('--v_size', type=int, default=16, help='The number of col in the block operation')
parser.add_argument('--run_type', type=str, default='cpu', help='The type of execution e.g. cpu, fpga')
parser.add_argument('--network', type=str, default='cnn', help='The type of execution e.g. cnn, mlp')


def main(args):
  print('[*] Arguments: %s' % args)
  print('[*] Read MNIST...')
  num_test_images = args.num_test_images
  images, labels = load_mnist('test', path='./data', max_ind=num_test_images)
  images, labels = images[:num_test_images, :, :], labels[:num_test_images]
  images = images.astype(np.float32)
  images = images/255.
  print('[*] The shape of image: %s' % str(images.shape))
  

  print('[*] Load the network...')
  if args.network == 'mlp': # Lab 2
    model_path = os.path.join('./pretrained_weights', 'mlp_iter_10000.caffemodel')
    net = MLP(model_path, args)
  elif args.network == 'cnn': # Lab 11
    model_path = os.path.join('./pretrained_weights', 'cnn_weights.txt')
    net = CNN(model_path, args)
  else:
    raise


  print('[*] Run tests...')		
  test_images = [images[i, :, :].copy() for i in xrange(num_test_images)]
  n_correct = 0
  start_time = time.time()

  for i in xrange(num_test_images):
    X = test_images[i]
    X = X.reshape((28*28)) # 28x28->784

    logit = net.inference(X)
    prediction = np.argmax(logit)
    label = labels[i,]

    n_correct += (label == prediction)
  

  print('[*] Statistics...')		
  model_stats = {
    'total_time': time.time()-start_time,
    'total_image': num_test_images,
    'accuracy': float(n_correct)/num_test_images,
    'avg_num_call': net.total_num_call[0]/num_test_images,
    'm_size': net.m_size,
    'v_size': net.v_size,
  }
  pp.pprint(model_stats)


if __name__ == '__main__':
  args = parser.parse_args()
  main(args)
