boot-sources += $(wildcard boot/*.s)
boot-sources += $(wildcard boot/*.c) 

boot-o += $(patsubst %.c,%.o, $(patsubst %.s,%.o, $(boot-sources))) 

