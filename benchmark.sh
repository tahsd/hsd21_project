#!/bin/bash

# You should compare the difference betwween the results of cpu vs fpga version.
# Analyze the results and include it in your report.

# Conv Lowering(CPU) - Acc: 1.0
sudo python eval.py --num_test_images 100 --v_size 8 --network cnn --run_type cpu
echo -e '\n=> Accuracy should be 1.0\n'

# Conv Lowering(FPGA) - Acc: 1.0
sudo python eval.py --num_test_images 100 --v_size 8 --network cnn --run_type fpga
echo -e '\n=> Accuracy should be 1.0'