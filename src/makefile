
CC := gcc
CFLAGS := -Wall -O2

# Source sets
APP_SRCS := MYASM.c cleaner.c memger.c sds.c
TEST_SRCS := cleaner.c memger.c sds.c testcleaner.c unity.c

.PHONY: all test clean

myasm: $(APP_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

all: myasm

test_runner: $(TEST_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

test: test_runner
	./test_runner

clean:
	rm -f myasm test_runner
