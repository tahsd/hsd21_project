#!/bin/bash

# Lab2 - Acc: 0.97
sudo python eval.py --num_test_images 100 --m_size 64 --v_size 64 --network mlp --run_type cpu
echo -e '\n=> Accuracy should be 0.97\n'

# MV - Acc: 0.97
sudo python eval.py --num_test_images 100 --m_size 64 --v_size 64 --network mlp --run_type fpga
echo -e '\n=> Accuracy should be 0.97\n'

# Conv Lowering(CPU) - Acc: 1.0
sudo python eval.py --num_test_images 100 --v_size 32 --network cnn --run_type cpu
echo -e '\n=> Accuracy should be 1.0\n'

# Conv Lowering(FPGA) - Acc: 1.0
# sudo python eval.py --num_test_images 100 --m_size 4 --v_size 4 --network cnn --run_type fpga
# echo -e '\n=> Accuracy should be 1.0'
