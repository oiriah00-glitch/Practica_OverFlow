CC      ?= gcc
CFLAGS  ?= -w -g -O0 -fno-stack-protector -fno-pie -U_FORTIFY_SOURCE
LDFLAGS ?= -no-pie -z execstack
SRC      = src/heapexample.c
SC_SRC   = shellcode/cat_passwd64.s
SC_BIN   = shellcode/cat_passwd64.bin

all: heapexample $(SC_BIN)

heapexample: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

$(SC_BIN): $(SC_SRC)
	as --64 -o shellcode/cat_passwd64.o $<
	objcopy -O binary -j .text shellcode/cat_passwd64.o $@

hex: $(SC_BIN)
	xxd -p $(SC_BIN) | tr -d '\n'; echo

heapexample32: $(SRC)
	$(CC) -m32 $(CFLAGS) $(LDFLAGS) -o $@ $<

checksec: heapexample
	checksec --file=./heapexample || true

run: heapexample
	./heapexample Hola

clean:
	rm -f heapexample heapexample32 *.o payload*.bin core core.*
	rm -f shellcode/cat_passwd64.o shellcode/cat_passwd64.bin

.PHONY: all hex checksec run clean
