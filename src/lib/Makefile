lib-sources += $(wildcard lib/*.s)
lib-sources += $(wildcard lib/*.c) 

lib-o += $(patsubst %.c,%.o, $(patsubst %.s,%.o, $(lib-sources))) 

