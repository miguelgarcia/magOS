kernel-arch-sources += $(wildcard arch/$(ARCH)/kernel/*.s)
kernel-arch-sources += $(wildcard arch/$(ARCH)/kernel/*.c) 

kernel-o += $(patsubst %.c,%.o, $(patsubst %.s,%.o, $(kernel-arch-sources))) 

