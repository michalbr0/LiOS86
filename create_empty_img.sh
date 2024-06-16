#!/bin/bash

image=hd.img

rm $image
fallocate -l 1G $image

fdisk $image << EOF
n
p
1
2048

a
t
c
w
EOF

lp=$(sudo losetup -f)

sudo losetup $lp -o 1048576 $image
sudo mkfs.fat $lp -n "LIOS86HD   "
sleep 1
sudo losetup -d $lp
sleep 1
