CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -Iinclude/
IMAGE_LDFLAGS=-melf_i386 --oformat elf32-i386 -Tlink.ld
LDFLAGS=-melf_i386 --oformat elf32-i386 -r
ASFLAGS=-felf

ARCH=i386

BOOT=image/boot.o
KERNEL=image/kernel.o

LIB=image/lib.o
IMAGE=image/image

include kernel/Makefile
include arch/$(ARCH)/kernel/Makefile

include boot/Makefile
include arch/$(ARCH)/boot/Makefile

include lib/Makefile
include arch/$(ARCH)/lib/Makefile

all: image

lib: $(lib-o) lib-link
boot: $(boot-o) boot-link
kernel: $(kernel-o) kernel-link

image: boot lib kernel image-link

lib-link:
	ld $(LDFLAGS) -o $(LIB) $(lib-o)

boot-link:
	ld $(LDFLAGS) -o $(BOOT) $(boot-o)

kernel-link:
	ld $(LDFLAGS) -o $(KERNEL) $(kernel-o)

image-link:
	ld $(IMAGE_LDFLAGS) -o $(IMAGE) $(BOOT) $(KERNEL) $(LIB)

clean:
	rm -f $(kernel-o)
	rm -f $(lib-o)
	rm -f $(boot-o)
	rm -f $(BOOT)
	rm -f $(KERNEL)
	rm -f $(LIB)
	rm -f $(IMAGE)

.s.o:
	nasm $(ASFLAGS) $< 
