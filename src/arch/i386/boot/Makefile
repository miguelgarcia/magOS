boot-arch-sources += $(wildcard arch/$(ARCH)/boot/*.s)
boot-arch-sources += $(wildcard arch/$(ARCH)/boot/*.c) 

boot-o += $(patsubst %.c,%.o, $(patsubst %.s,%.o, $(boot-arch-sources))) 

