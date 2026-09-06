CC = gcc-11

TARGETS = leak_demo vuln_service write_demo
FORTIFIED_TARGETS = leak_demo_fortified vuln_service_fortified

.PHONY: all fortified clean

all: $(TARGETS)

fortified: $(FORTIFIED_TARGETS)

write_demo: write_demo.c
	$(CC) -fno-pie -no-pie -o $@ $<

leak_demo_fortified: leak_demo.c
	$(CC) -O1 -o $@ $<

vuln_service_fortified: vuln_service.c
	$(CC) -O1 -o $@ $<

%: %.c
	$(CC) -o $@ $<

clean:
	rm -f $(TARGETS) $(FORTIFIED_TARGETS)
