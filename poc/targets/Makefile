CC = gcc-11

TARGETS = leak_demo vuln_service write_demo

.PHONY: all clean

all: $(TARGETS)

write_demo: write_demo.c
	$(CC) -fno-pie -no-pie -o $@ $<

%: %.c
	$(CC) -o $@ $<

clean:
	rm -f $(TARGETS)
