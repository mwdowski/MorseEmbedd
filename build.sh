#!/bin/bash
# Set the variables according to your Buildroot configuration
BRPATH=/malina/wdowskim/buildroot-2023.02
PATH=$BRPATH/output/host/usr/bin:$PATH
make ARCH=arm CROSS_COMPILE=aarch64-none-linux-gnu-
