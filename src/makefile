SRCS := $(wildcard *.c)

myasm: $(SRCS)
	gcc -o $@ $^

all: myasm

clean:
	rm -f myasm
