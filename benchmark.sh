#!/bin/bash

# Acc: 0.97
sudo python eval.py --num_test_images 100 --m_size 64 --v_size 64 --network mlp --run_type fpga
echo -e '\n=> Accuracy should be 0.97\n'

# Acc: 1.0
sudo python eval.py --num_test_images 100 --v_size 8 --network cnn --run_type fpga
echo -e '\n=> Accuracy should be 1.0'
