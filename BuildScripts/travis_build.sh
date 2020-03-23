#!/usr/bin/env bash

set -e

export NUM_JOBS=1

mkdir build
cd build
cmake -DUSE_CUDA=OFF ..
make
bin/Main