CC := gcc

CFLAGS := -Wall

PROG := fuzzer
OBJS := help.o util.o

all: $(PROG)
	./fuzzer ./extractor_x86_64

%.o: %.c
	$(CC) -c $(CFLAGS) help.c
	$(CC) -c $(CFLAGS) util.c

$(PROG): $(OBJS)
	$(CC) -g -o $@ $^ -lm



#helper function
arch_basic:
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c vide.txt > archive_basic.tar

medium_arch:
	tar --posix --pax-option delete=".*" --pax-option delete="*time*" --no-xattrs --no-acl --no-selinux -c fable.txt wikipedia_pokemon.txt > archive_medium.tar

visu:
	hexdump -C archive_basic.tar > visu_basic.txt
	hexdump -C archive_medium.tar > visu_medium.txt

clean:
	rm *ide.txt
	touch vide.txt