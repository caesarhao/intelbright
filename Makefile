all: intelbright

intelbright: intelbright.c
	gcc -o $@ $<

install:
	cp intelbright /usr/bin/
