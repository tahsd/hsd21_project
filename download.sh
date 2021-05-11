#!/bin/bash

# the links below expire soon
wget -O data/t10k-images.idx3-ubyte https://dl.dropbox.com/s/mdwy0kzf57nfl5f/t10k-images.idx3-ubyte
wget -O data/t10k-labels.idx1-ubyte https://dl.dropbox.com/s/q6gmxa2euc2bv98/t10k-labels.idx1-ubyte
wget -O pretrained_weights/mlp_iter_10000.caffemodel https://dl.dropbox.com/s/tsubzfrnuci6n5h/mlp_iter_10000.caffemodel
wget -O pretrained_weights/cnn_weights.txt https://dl.dropbox.com/s/w9wga66reowm1fv/cnn_weights.txt
