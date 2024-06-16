#!/bin/bash

# ===================================================================
# Copies a file into the root directory on the first partition
# of the specified disk image file. Filename is preserved.
#
# Argument 1: source file
# Argument 2: destination file (image disk)
# ===================================================================

if [ $# -ne 2 ]
    then
        echo "2 arguments should be supplied"
        exit 1
fi

lp=$(sudo losetup -f)

sudo losetup $lp $2
sudo partprobe $lp

part="${lp}p1"
echo $part

sudo mkdir /loopfs
sudo mount -o loop $part /loopfs

base_name=$(basename ${1})
dest="/loopfs/${base_name}"

sudo cp $1 $dest

sudo umount /loopfs
sudo rm -rf /loopfs

sudo losetup -d $lp
