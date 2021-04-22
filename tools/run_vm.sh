#!/bin/bash

qemu-system-i386 -boot a -m 32 -fda `pwd`/vm/floppy.img -d cpu

