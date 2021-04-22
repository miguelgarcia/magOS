#!/bin/bash

mkdir tmpimage
sudo mount -o loop vm/floppy.img tmpimage
sudo cp src/image/image tmpimage/kernel
sudo umount tmpimage
rmdir tmpimage
