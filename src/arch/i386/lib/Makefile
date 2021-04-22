lib-arch-sources += $(wildcard arch/$(ARCH)/lib/*.s)
lib-arch-sources += $(wildcard arch/$(ARCH)/lib/*.c) 

lib-o += $(patsubst %.c,%.o, $(patsubst %.s,%.o, $(lib-arch-sources))) 

