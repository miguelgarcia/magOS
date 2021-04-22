kernel-sources += $(wildcard kernel/*.s)
kernel-sources += $(wildcard kernel/*.c) 

kernel-o += $(patsubst %.c,%.o, $(patsubst %.s,%.o, $(kernel-sources))) 

